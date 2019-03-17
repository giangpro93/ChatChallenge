/**
 * @file mainclass.cpp
 * @brief this is the cpp file for "mainclass" class
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#include <QDebug>
#include "mainclass.h"

typedef std::pair<QString, QObject*> chatWindowPair;

MainClass::MainClass(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief init save the engine and component pointer
 * @param engine the pointer to the engine
 * @param component the pointer to the component
 */
void MainClass::init(QQmlApplicationEngine *engine, QQmlComponent *component)
{
    this->engine=engine;
    this->component=component;
}

/**
 * @brief createMainWindow create new main.qml window
 * @param userIP an integer storing the order of this MainClass in the engine
 */
void MainClass::createMainWindow(int userIP)
{
    engine->load(QUrl(QStringLiteral("qrc:/Main.qml")));
    mainQMLObject = engine->rootObjects()[userIP];
    QQmlProperty::write(mainQMLObject,"userIP",userIP);
    QObject::connect(mainQMLObject, SIGNAL(userloggedin(QString)),this, SLOT(login(QString)));
    QObject::connect(mainQMLObject, SIGNAL(userloggedout()),this, SLOT(logout()));
    QObject::connect(mainQMLObject, SIGNAL(newconversation(QString)),this, SLOT(createNewChatWindow(QString)));
}

/**
 * @brief login log the user in
 * @param username a string storing the username
 */
void MainClass::login(QString username)
{
    this->username=username;
}

/**
 * @brief logout log the user out
 */
void MainClass::logout()
{
    this->username="";
    while (!chatWindowObjects.empty()) {
        qDebug() << "Close chat window with: " + chatWindowObjects.begin()->first;
        QMetaObject::invokeMethod(chatWindowObjects.begin()->second,"close");
        // the close method will cause a closing signal to call the closeSelectWindow method
        // therefore, there's no need to call erase()
    }
}

/**
 * @brief createNewChatWindow create a new chat window with given partner
 * @param partner a string storing the partner's username
 */
void MainClass::createNewChatWindow(QString partner)
{
    if (chatWindowObjects.find(partner) == chatWindowObjects.end()) {
        qDebug() << "Open new chat window with: " + partner;
        QObject *object = component->create();
        QQmlProperty::write(object,"username",username);
        QQmlProperty::write(object,"partner",partner);
        chatWindowObjects.insert(chatWindowPair(partner,object));
        QObject::connect(&(*object),SIGNAL(closechatwindow(QString)),this,SLOT(closeSelectWindow(QString)));
        QVariant QVusername = username;
        QVariant QVpartner = partner;
        QMetaObject::invokeMethod(mainQMLObject,"newWindow",Q_ARG(QVariant,QVusername),Q_ARG(QVariant,QVpartner));
    }
}

/**
 * @brief closeSelectWindow close the selected window with given partner
 * @param partner a string storing the partner's username
 */
void MainClass::closeSelectWindow(QString partner)
{
    chatWindowObjects.erase(partner);
}

/**
 * @brief updateNewMessage update the new message to user's chat window
 * @param partner a string storing the partner's username
 * @param sender a string storing the sender's username
 * @param message a string storing the message
 * @param isNew a string storing "True" or "False", corresponding to this is a new message or not
 */
void MainClass::updateNewMessage(QString partner, QString sender, QString message, QString isNew)
{
    QVariant QVsender = sender;
    QVariant QVmessage = message;
    QVariant QVisNew = isNew;

    std::map<QString, QObject*>::iterator it;
    it = chatWindowObjects.find(partner);

    if (it == chatWindowObjects.end()) {
        createNewChatWindow(partner);
    }
    else {
        QObject *object = it->second->findChild<QObject*>("wnd");
        QMetaObject::invokeMethod(object, "receiveMessage",
                                  Q_ARG(QVariant,QVsender),Q_ARG(QVariant, QVmessage),Q_ARG(QVariant, QVisNew));
    }
}
