import QtQuick 2.12
import QtQuick.Controls 2.5

Frame{
    property int pageHeight: frameListView.height/(frameListView.count == 0 ? 1 : frameListView.count)
    property int finalX: -1
    property int finalY: -1

    Column{
        width: parent.width*0.5
        height: parent.height
        spacing: 10

        PageListPathView{
            id: pageListPathView
            width: parent.width
            height: parent.height
        }

        Text {
            id: statusUpdate
            //text: demandPagingCPP.ExtraTip
            color: "blue"
            font.pointSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            height: parent.height*0.2
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    FrameListView{
        id: frameListView
        width: parent.width*0.2
        height: parent.height
        anchors.right: parent.right
    }

    Rectangle{
        id: animationRect
        visible: false
        x: (pageListPathView.count > 0 ? pageListPathView.currentItem.x : 0)
        y: (pageListPathView.count > 0 ? pageListPathView.currentItem.y : 0)
        color: "transparent"
        height: pageHeight
        width: height*0.75

        Image {
            source: "/local/assets/page.svg"
            sourceSize.width: parent.width*0.9
            sourceSize.height: parent.height*0.9
            anchors.centerIn: parent
        }

        Text {
            text: (pageListPathView.count > 0 ? demandPagingCPP.FirstPage.Id : "")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 16
            //color: "white"
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            width: parent.width*0.9
            height: parent.height*0.9

        }
    }

    SequentialAnimation{
        id: displaceAnimation
        ParallelAnimation{
            NumberAnimation{
                target: animationRect
                property: "x"
                to: finalX
                duration: 500
            }

            NumberAnimation{
                target: animationRect
                property: "y"
                to: finalY
                duration: 500
            }
        }

        PropertyAnimation{
            target: animationRect
            property: "visible"
            to: false
            duration: 0
        }
    }

    Connections{
        target: demandPagingCPP
        onMoveNextPage:{
            finalX = frameListView.x
            finalY = frameListView.y + pageHeight*frameIndex
            animationRect.visible = true
            displaceAnimation.start()
        }
    }
}
