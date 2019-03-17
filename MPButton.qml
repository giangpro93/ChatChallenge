/**
 * @file MPButton.qml
 * @brief MPButton stands for "multi-purpose button"
 * @author Giang Nguyen
 * Contact: giangpro93@gmail.com
 */

import QtQuick 2.9

Rectangle {
    id: mpbtn

    property string label
    property color textColor: "white"
    property int fontSize: 15

    property color btnColor: "grey"
    property color hoverColor: "orange"
    property color pressColor: "black"

    property int borderWidth: 1
    property int borderRadius: 3
    property color borderColor: "black"

    signal pressBtn

    radius: borderRadius
    border {
        color: borderColor
        width: borderWidth
    }
    color: btnColor
    height: buttonLabel.height * 1.5
    width: buttonLabel.width + 40

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: label
        color: textColor
        font.pointSize: fontSize
    }

    states: [
        State {
            name:"Hovering"
            PropertyChanges {
                target: mpbtn
                color: hoverColor
            }
        },
        State {
            name:"Pressed"
            PropertyChanges {
                target: mpbtn
                color: pressColor
            }
        }
    ]

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: parent.state="Hovering"
        onExited: parent.state=""
        onClicked: pressBtn()
        onPressed: parent.state="Pressed"
        onReleased: {
            if (containsMouse)
                parent.state="Hover";
            else
                parent.state="";
        }
    }
}
