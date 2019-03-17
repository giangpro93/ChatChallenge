/**
 * @file chatserver.h
 * @brief this class simulates the chat server
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QString>
#include "connection.h"
#include "user.h"
#include "mainclass.h"

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);

    /**
     * @brief addNewMainClass store the MainClass pointer with corresponding order in the engine to MainClassList map
     * @param mainClass the MainClass pointer
     * @param userIP an integer storing the order of the MainClass in the engine
     */
    void addNewMainClass(MainClass *mainClass, int userIP);

    /**
     * @brief registerClient register a new user
     * @param username a string storing the username
     */
    Q_INVOKABLE void registerClient(QString username);

    /**
     * @brief userExist check if the username exists
     * @param username a string storing the username
     * @return a boolean representing if username exists or not
     */
    Q_INVOKABLE bool userExist(QString username);

    /**
     * @brief userLogin log the user in
     * @param username a string storing the username
     * @param userIP an integer storing the order of the MainClass in the engine
     */
    Q_INVOKABLE void userLogin(QString username, int userIP);

    /**
     * @brief userLogout log the user out
     * @param username a string storing the username
     */
    Q_INVOKABLE void userLogout(QString username);

    /**
     * @brief getRecentMessage get all the messages between 2 users
     * @param username a string storing the username
     * @param partner a string storing the partner's username
     */
    Q_INVOKABLE void getRecentMessage(QString username, QString partner);

    /**
     * @brief sendMessage send the message from sender to receiver
     * @param message a string storing the message
     * @param sender a string storing the sender's username
     * @param receiver a string storing the receiver's username
     */
    Q_INVOKABLE void sendMessage(QString message, QString sender, QString receiver);

public slots:
    /**
     * @brief handleUpdateToUser call the updateNewMessage in the MainClass corresponding to the username
     * @param username a string storing the username
     * @param partner a string storing the partner's username
     * @param sender a string storing the sender's username
     * @param message a string storing the message
     * @param isNew a string storing "True" or "False", corresponding to this is a new message or not
     */
    void handleUpdateToUser(QString username, QString partner, QString sender, QString message,QString isNew);

private:
    /**
     * @param clients a map storing the user's objects corresponding to the username
     */
    std::map<QString, User*> clients;

    /**
     * @param connections a map storing the connection objects corresponding to the combineID of 2 users
     */
    std::map<QString, Connection*> connections;

    /**
     * @param MainClassList a map storing the MainClass corresponding to the order of the MainClass in the engine
     */
    std::map<int, MainClass*> MainClassList;

    /**
     * @param userIPList a map storing the order of the MainClass in the engine that the corresponding user is logging in
     */
    std::map<QString, int> userIPList;

    /**
     * @brief combine combine 2 strings
     * @param A a string
     * @param B a string
     * @return the combine of 2 strings
     */
    QString combine(QString A, QString B);
};

#endif // CHATSERVER_H
