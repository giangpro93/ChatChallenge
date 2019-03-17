/**
 * @file chatserver.cpp
 * @brief this is the cpp file for "chatserver" class
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

#include <QtDebug>
#include "chatserver.h"

typedef std::pair<QString, User*> userPair;
typedef std::pair<QString, Connection*> connectionPair;
typedef std::pair<int, MainClass*> mainClassPair;

ChatServer::ChatServer(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief addNewMainClass store the MainClass pointer with corresponding order in the engine to MainClassList map
 * @param mainClass the MainClass pointer
 * @param userIP an integer storing the order of the MainClass in the engine
 */
void ChatServer::addNewMainClass(MainClass *mainClass,int userIP)
{
    MainClassList.insert(mainClassPair(userIP,mainClass));
}

/**
 * @brief registerClient register a new user
 * @param username a string storing the username
 */
void ChatServer::registerClient(QString username)
{
    if (clients.find(username) == clients.end()) {
        User* newClient = new User();
        newClient->setUsername(username);
        clients.insert(userPair(username,newClient));
        qDebug() << "Create new user successfully: "+username;
    }
    else {
        qDebug() << "User already exists";
    }
}

/**
 * @brief userExist check if the username exists
 * @param username a string storing the username
 * @return a boolean representing if username exists or not
 */
bool ChatServer::userExist(QString username)
{
    if (clients.find(username) == clients.end()) {
        return false;
    }
    else return true;
}

/**
 * @brief userLogin log the user in
 * @param username a string storing the username
 * @param userIP an integer storing the order of the MainClass in the engine
 */
void ChatServer::userLogin(QString username, int userIP)
{
    userIPList[username] = userIP;
    std::map<QString, User*>::iterator it;
    it = clients.find(username);
    if (it != clients.end()) {
        it->second->setStatus(true);
        qDebug() << "Logged in successfully: "+username;
    }
    else {
        qDebug() << "User does not exist";
    }
}

/**
 * @brief userLogout log the user out
 * @param username a string storing the username
 */
void ChatServer::userLogout(QString username)
{
    userIPList.erase(username);
    std::map<QString, User*>::iterator it;
    it = clients.find(username);
    if (it != clients.end()) {
        it->second->setStatus(false);
        qDebug() << "Logged out successfully: "+username;
    }
    else {
        qDebug() << "User does not exist";
    }
}

/**
 * @brief getRecentMessage get all the messages between 2 users
 * @param username a string storing the username
 * @param partner a string storing the partner's username
 */
void ChatServer::getRecentMessage(QString username, QString partner)
{
    QString combineID=combine(username,partner);

    std::map<QString, Connection*>::iterator it;
    it = connections.find(combineID);

    if (it != connections.end()){
        it->second->getMessage(username);
    }
}

/**
 * @brief sendMessage send the message from sender to receiver
 * @param message a string storing the message
 * @param sender a string storing the sender's username
 * @param receiver a string storing the receiver's username
 */
void ChatServer::sendMessage(QString message, QString sender, QString receiver)
{
    QString combineID=combine(sender, receiver);

    std::map<QString, Connection*>::iterator it;
    it = connections.find(combineID);

    Connection *connection = nullptr;
    if (it == connections.end()) {
        connection = new Connection();
        connection->setUser(sender, receiver);
        connections.insert(connectionPair(combineID,connection));
        QObject::connect(&(*connection), &Connection::sendMessageToUser, this, &ChatServer::handleUpdateToUser);
    }
    else connection = it->second;

    // Store message in the connection
    connection->storeMessage(sender,message);

    if (clients.find(receiver)->second->checkStatus()) {
        handleUpdateToUser(receiver, sender, sender, message, "True");
    }
}

/**
 * @brief handleUpdateToUser call the updateNewMessage in the MainClass corresponding to the username
 * @param username a string storing the username
 * @param partner a string storing the partner's username
 * @param sender a string storing the sender's username
 * @param message a string storing the message
 * @param isNew a string storing "True" or "False", corresponding to this is a new message or not
 */
void ChatServer::handleUpdateToUser(QString username, QString partner, QString sender, QString message, QString isNew)
{
    MainClassList[userIPList[username]]->updateNewMessage(partner, sender, message, isNew);
}

/**
 * @brief combine combine 2 strings
 * @param A a string
 * @param B a string
 * @return the combine of 2 strings
 */
QString ChatServer::combine(QString A, QString B)
{
    return (A<B ? A+B : B+A);
}
