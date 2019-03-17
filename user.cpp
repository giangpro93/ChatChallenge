/**
 * @file user.cpp
 * @brief this is the cpp file for "user" class
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#include "user.h"

User::User(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief setUsername save the username
 * @param username a string storing the username
 */
void User::setUsername(QString username)
{
    this->username=username;
}

/**
 * @brief setStatus change user's status
 * @param isOnline a boolean storing user's status: true or false, corresponding to online or offline
 */
void User::setStatus(bool isOnline)
{
    this->isOnline=isOnline;
}

/**
 * @brief checkStatus
 * @return return user's status
 */
bool User::checkStatus()
{
    return isOnline;
}
