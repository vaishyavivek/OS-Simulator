import QtQuick 2.12
import QtQuick.Controls 2.5
import "../qml/CustomComponents"

Rectangle {
    id: demandPaging
    color: "transparent"

    Column{
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        InputFrame{
            id: inputFrame
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row{
            width: parent.width
            height: (parent.height - inputFrame.height)*0.6 - 20
            spacing: 10

            AnimationFrame{
                id: animationFrame
                width: parent.width*0.75 - 10
                height: parent.height
            }

            ResultFrame{
                width: parent.width*0.25
                height: parent.height
            }
        }

        FrameHistory{
            id: frameList
            width: parent.width
            height: (parent.height - inputFrame.height)*0.4
            anchors.bottomMargin: 10
        }
    }
}
