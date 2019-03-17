/**
 * @file ChatWindowWrapper.qml
 * @brief The window wrapper for the chatwindow.qml
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

import QtQuick 2.9
import QtQuick.Window 2.3

Window {
    id: wrapper
    property string username
    property string partner
    visible: true
    x: Screen.width/2-600
    y: Screen.height/4
    width: 600
    height: 500
    title: "to: " + partner
    signal closechatwindow(string object)

    // trigger the closechatwindow signal for given partner
    // if the IDE said that this is invalid. It's a false positive. The program works fine.
    onClosing: closechatwindow(partner)

    ChatWindow {
        id: chatwindow
        objectName: "wnd"

        Connections {
            target: wrapper
            onUsernameChanged: chatwindow.username = wrapper.username
            onPartnerChanged: chatwindow.partner = wrapper.partner
        }
    }
}


