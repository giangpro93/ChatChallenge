/**
 * @file user.h
 * @brief this class stores user's credential including: username, status (online/offline)
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
class User : public QObject
{
    Q_OBJECT
    public:
        explicit User(QObject *parent = nullptr);

        /**
         * @brief setUsername save the username
         * @param username a string storing the username
         */
        void setUsername(QString username);

        /**
         * @brief setStatus change user's status
         * @param isOnline a boolean storing user's status: true or false, corresponding to online or offline
         */
        void setStatus(bool isOnline);

        /**
         * @brief checkStatus
         * @return return user's status
         */
        bool checkStatus();

    private:
        /**
         * @param username store the username
         */
        QString username;

        /**
         * @param isOnline store user's status
         */
        bool isOnline;
};

#endif // USER_H
