import QtQuick 2.6
import QtQuick.Controls 2.1

Button {
    id: rTextButton
    property string hoverText: ""
    property bool toolTipEnabled: hoverText.length > 0

    hoverEnabled: true
    padding: 0

    contentItem: Item{
        width: rTextButton.width
        height: rTextButton.height
        Rectangle{
            anchors.fill: parent
            opacity: 0.8
            color: "#0a80a8"
            radius: 5
        }

        Text {
            width: parent.width
            height: parent.height
            text: rTextButton.text
            font.family: "Sans Serif"
            font.pointSize: 12
            clip: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

        }
    }

    background: Rectangle {
        id: backgroundRect
        width: rTextButton.width - 2
        height: rTextButton.height - 2
        anchors.centerIn: parent
        opacity: enabled ? 1 : 0.4
        color: "transparent"
        radius: 5
        border.color: "#095b81"
        border.width: 1
        Rectangle{
            id: animatingRect
            anchors.fill: parent
            opacity: (color === "transparent" ? 0.3 : 0.6)
            radius: 5
            color: "transparent"
        }
    }

    PropertyAnimation{
        id: mouseEnteredAnimation
        target: animatingRect
        property: "color"
        to: "grey"
        duration: 250//rFileSystem.GlobalAnimationDuration
    }

    PropertyAnimation{
        id: mouseExitedAnimation
        target: animatingRect
        property: "color"
        to: "transparent"
        duration: 250//rFileSystem.GlobalAnimationDuration
    }

    ToolTip{
        id: tooltip
        visible: toolTipEnabled && parent.hovered
        text: hoverText
        delay: 500
        timeout: 1000
        contentItem: Text {
            text: tooltip.text
            font: tooltip.font
            color: "#312d2d"
        }
        background: Rectangle {
            color: "white"
        }
    }

    onHoveredChanged: {
        if(hovered)
            mouseEnteredAnimation.start()
        else if(!checked)
            mouseExitedAnimation.start()
    }

    onCheckedChanged: checked ? mouseEnteredAnimation.start() : mouseExitedAnimation.start()

}
