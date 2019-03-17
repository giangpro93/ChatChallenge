/**
 * @file mainclass.h
 * @brief this class is the sub-app for distinct user, handle login, logout, window chats, update message
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QObject>
#include <QString>

class MainClass : public QObject
{
    Q_OBJECT
    public:
        explicit MainClass(QObject *parent = nullptr);

        /**
         * @brief init save the engine and component pointer
         * @param engine the pointer to the engine
         * @param component the pointer to the component
         */
        void init(QQmlApplicationEngine *engine, QQmlComponent *component);

        /**
         * @brief createMainWindow create new main.qml window
         * @param userIP an integer storing the order of this MainClass in the engine
         */
        void createMainWindow(int userIP);

    public slots:
        /**
         * @brief login log the user in
         * @param username a string storing the username
         */
        void login(QString username);

        /**
         * @brief logout log the user out
         */
        void logout();

        /**
         * @brief createNewChatWindow create a new chat window with given partner
         * @param partner a string storing the partner's username
         */
        void createNewChatWindow(QString partner);

        /**
         * @brief closeSelectWindow close the selected window with given partner
         * @param partner a string storing the partner's username
         */
        void closeSelectWindow(QString partner);

        /**
         * @brief updateNewMessage update the new message to user's chat window
         * @param partner a string storing the partner's username
         * @param sender a string storing the sender's username
         * @param message a string storing the message
         * @param isNew a string storing "True" or "False", corresponding to this is a new message or not
         */
        void updateNewMessage(QString partner, QString sender, QString message, QString isNew);

    private:
        /**
         * @param engine store the pointer to the engine
         */
        QQmlApplicationEngine *engine=nullptr;

        /**
         * @param component store the pointer to the component
         */
        QQmlComponent *component=nullptr;

        /**
         * @param mainQMLObject store the pointer to the main.qml object corresponding to this MainClass
         */
        QObject *mainQMLObject=nullptr;

        /**
         * @param username a string storing the username
         */
        QString username;

        /**
         * @param chatWindowObjects a map storing the chat window object corresponding to a partner's username
         */
        std::map<QString, QObject*> chatWindowObjects;
};

#endif // MAINCLASS_H
