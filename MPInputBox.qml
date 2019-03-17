/**
 * @file MPInputBox.qml
 * @brief MPInputBox stands for "multi-purpose InputBox"
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

import QtQuick 2.9

FocusScope {
    id: inputbox

    property string content: textinput.text
    property string hint

    signal clear

    onClear: {
        textinput.text = ""
    }

    Text {
        id: placeholder
        anchors.fill: parent
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter

        text: hint
        color: "lightgrey"
        font.pointSize: 14
    }

    MouseArea {
        anchors.fill: parent
        onClicked: inputbox.focus = true
    }

    TextInput {
        id: textinput
        anchors.fill: parent
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        focus: true
        selectByMouse: true
        font.pointSize: 14
    }

    states: [
        State {
            name: "showPlaceholder"
            when:(textinput.text === "")
            PropertyChanges { target: placeholder; opacity:1 }
            PropertyChanges { target: textinput; opacity:0 }
        },
        State {
            name: "showTextInput"
            when:(textinput.text !== "")
            PropertyChanges { target: placeholder; opacity:0 }
            PropertyChanges { target: textinput; opacity:1 }
        }
    ]
}
