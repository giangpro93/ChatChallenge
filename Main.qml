/**
 * @file Main.qml
 * @brief The main user interface
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

import QtQuick 2.9
import QtQuick.Window 2.3

Window {
    id: onchatmain
    visible: true
    x: 0
    y: 0
    width: 600
    height: 500
    title: "Login to your OnChat account"
    property int userIP
    signal userloggedin(string object)
    signal userloggedout
    signal newconversation(string object)

    // if the IDE said that this is invalid. It's a false positive. The program works fine.
    onClosing: logout()

    // get the recent messages when user opens a new chat window
    function newWindow (usernameinput, partnerinput) {
        chatServer.getRecentMessage(usernameinput,partnerinput);
    }

    // log the user in
    function login () {
        onchatmain.title = "Welcome " + username.content
        userloggedin(username.content)
        if (!chatServer.userExist(username.content))
            chatServer.registerClient(username.content)
        chatServer.userLogin(username.content,userIP)
        loginInterface.visible = false
        userInterface.visible = true
    }

    // start a new conversation
    function startnewconversation () {
        if (chatServer.userExist(partnerID.content))
            newconversation(partnerID.content)
    }

    // log the user out
    function logout () {
        onchatmain.title = "Login to your OnChat account"
        chatServer.userLogout(username.content);
        userloggedout()
        userInterface.visible = false
        loginInterface.visible = true
    }

    Item {
        id: loginInterface
        visible: true

        anchors.fill:parent
        width: parent.width
        height: parent.height

        MPInputBox {
            id: username
            hint: "Type your username"
            Keys.onReturnPressed: login()
            anchors.bottom: loginbtn.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: loginbtn.width
            height: loginbtn.height

            Rectangle {
                anchors.fill: parent
                opacity: 0.15
                color: "lightgrey"
                border{
                    width: 1
                    color: "black"
                }
            }
        }

        MPButton {
            id: loginbtn
            label: "Login/Create new account"
            anchors.centerIn: parent
            onPressBtn: login()
        }
    }

    Item {
        id: userInterface
        visible: false

        anchors.fill:parent
        width: parent.width
        height: parent.height

        MPInputBox {
            id: partnerID
            hint: "Type your partner username"
            Keys.onReturnPressed: startnewconversation()
            anchors.bottom: newconversationbtn.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: loginbtn.width
            height: loginbtn.height

            Rectangle {
                anchors.fill: parent
                opacity: 0.15
                color: "lightgrey"
                border{
                    width: 1
                    color: "black"
                }
            }
        }

        MPButton {
            id: newconversationbtn
            label: "Start new conversation"
            anchors.bottom: logoutbtn.top
            anchors.horizontalCenter: parent.horizontalCenter
            onPressBtn: startnewconversation()
        }

        MPButton {
            id: logoutbtn
            label: "Log out"
            anchors.centerIn: parent
            onPressBtn: logout()
        }
    }
}

