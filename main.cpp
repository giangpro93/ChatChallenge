/**
 * @file main.cpp
 * @brief this file create and run the app
 *
 * This app is a chat server simulator. Some of the key features:
 * + Create multiple apps for testing the server, default is 2, can add more by editing this file
 * + Create new user, login, logout
 * + Store multiple users and users' messages
 * + Get recent messages when open a chat window to a partner
 * + When logged in, automatically open a chat window when there's an incoming message.
 * + Send message when the partner is offline, store message so that the partner can see it later.
 * ps: All data only exist when the app is still running. In other words, data will disappear when close the app
 *
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QQmlComponent>
#include "QtDebug"
#include "mainclass.h"
#include "chatserver.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create new engine
    QQmlApplicationEngine *engine = new QQmlApplicationEngine();

    // Create new component for making multiple chat windows
    QQmlComponent *component = new QQmlComponent(&(*engine),QUrl(QStringLiteral("qrc:/ChatWindowWrapper.qml")));

    // Create new ChatServer and make it callable from QML
    qmlRegisterType<ChatServer>("CS", 1, 0, "ChatServer"); // http://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterType
    ChatServer *chatServer = new ChatServer();
    engine->rootContext ()->setContextProperty ("chatServer", chatServer);

    // Create new app for the first user
    MainClass *myClass0 = new MainClass();
    myClass0->init(engine, component);
    myClass0->createMainWindow(0);
    chatServer->addNewMainClass(myClass0,0);

    // Create new app for the second user
    MainClass *myClass1 = new MainClass();
    myClass1->init(engine, component);
    myClass1->createMainWindow(1);
    chatServer->addNewMainClass(myClass1,1);

    // Run the app
    int appResult = app.exec();
    return appResult;
}
