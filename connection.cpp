/**
 * @file connection.cpp
 * @brief this is the cpp file for "connection" class
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#include <QtDebug>
#include <QObject>
#include "connection.h"

Connection::Connection(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief setUser save the users' username
 * @param user1 a string storing the first username
 * @param user2 a string storing the second username
 */
void Connection::setUser(QString user1, QString user2)
{
    this->user1=user1;
    this->user2=user2;
}

/**
 * @brief storeMessage save the message
 * @param sender a string storing the sender's username
 * @param message a string storing the message
 */
void Connection::storeMessage(QString sender, QString message)
{
    messageStruct *newMessage = new messageStruct();
    newMessage->sender = sender;
    newMessage->message = message;
    newMessage->next = allMessages;
    allMessages = newMessage;
}

/**
 * @brief getMessage get all the messages
 * @param user a string storing the user's username that requested to get the messages
 */
void Connection::getMessage(QString user)
{
    QString partner = (user == user1) ? user2 : user1;
    messageStruct *messageIterator = allMessages;
    while (messageIterator != nullptr) {
        emit sendMessageToUser(user, partner, messageIterator->sender, messageIterator->message, "False");
        messageIterator = messageIterator->next;
    }
}
