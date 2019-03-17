/**
 * @file connection.h
 * @brief this class stores the messages between 2 users
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

struct messageStruct {
    QString sender, message;
    messageStruct *next;
};

class Connection : public QObject
{
    Q_OBJECT
    public:
        explicit Connection(QObject *parent = nullptr);

        /**
         * @brief setUser save the users' username
         * @param user1 a string storing the first username
         * @param user2 a string storing the second username
         */
        void setUser(QString user1, QString user2);

        /**
         * @brief storeMessage save the message
         * @param sender a string storing the sender's username
         * @param message a string storing the message
         */
        void storeMessage(QString sender, QString message);

        /**
         * @brief getMessage get all the messages
         * @param user a string storing the user's username that requested to get the messages
         */
        void getMessage(QString user);

    signals:
        /**
         * @brief sendMessageToUser a signal to chat server to send message to user
         * @param username a string storing the receiver's username
         * @param partner a string storing the partner's username
         * @param sender a string storing the sender's username
         * @param message a string storing the message
         * @param isNew a string storing "True" or "False", corresponding to this is a new message or not, default = "False"
         */
        void sendMessageToUser(QString username, QString partner, QString sender, QString message, QString isNew);

    private:
        /**
         * @param user1 store the first username
         * @param user2 store the second username
         */
        QString user1, user2;

        /**
         * @param allMessages the first pointer of a linked-list of messageStruct, in which store the messages.
         */
        messageStruct *allMessages=nullptr;
    };

#endif // CONNECTION_H
