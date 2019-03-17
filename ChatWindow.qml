/**
 * @file ChatWindow.qml
 * @brief The chat window
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    id: root

    property string username
    property string partner

    anchors.fill: parent

    ListModel {
        id: messages
    }
    ScrollView {
        width: parent.width-14
        height: parent.height-sendbtn.height-separateLine.height-10
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        clip:true
        ListView {
            id: messagebox
            spacing: 5

            model: messages
            clip: true
            delegate: Component {
                Rectangle {
                    radius: 15
                    height: textElement.height+20
                    width: textElement.width+30
                    color: (content.indexOf("Me (") === 0) ? "lightblue" : "lightgrey"
                    anchors.left: (content.indexOf("Me (") !== 0) ? parent.left : undefined
                    anchors.right: (content.indexOf("Me (") === 0) ? parent.right : undefined
                    Text {
                        id: textElement
                        font.pointSize: 14
                        text: content
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    // send a message
    function sendMessage() {
        var newMessage = inputbox.content
        inputbox.clear()
        messages.append({content: "Me (" + username + "): " + newMessage})
        messagebox.positionViewAtEnd()
        chatServer.sendMessage(newMessage,username,partner)
    }

    // receive a message
    function receiveMessage(sender,message,isNew) {
        sender = (sender === username) ? "Me (" + username + ")" : sender;
        if (isNew === "True")
            messages.append({content: sender + ": " + message})
        else
            messages.insert(0,{content: sender + ": " + message});
        messagebox.positionViewAtEnd()
    }

    Rectangle {
        id: separateLine
        height: 1
        width: parent.width
        color: "grey"
        anchors.bottom: sendbtn.top
    }

    MPButton {
        id: sendbtn
        label: "Send"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onPressBtn: sendMessage()
    }

    MPInputBox {
        id: inputbox
        hint: "Type a message..."
        Keys.onReturnPressed: sendMessage()
        width: parent.width-sendbtn.width-20
        height: sendbtn.height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
