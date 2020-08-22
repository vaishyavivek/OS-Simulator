import QtQuick 2.12
import QtQuick.Controls 2.5

PathView{
    id: pageList
    model: demandPagingCPP.PageList
    currentIndex: 0

    delegate: Rectangle{
        opacity: pageList.currentIndex == index ? 1 : 0.3
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
            text: model.modelData.Id
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
            horizontalAlignment: Text.AlignHCenter
            //color: "white"
            anchors.centerIn: parent
            width: parent.width*0.9
            height: parent.height*0.9

        }
    }

    clip: true
    pathItemCount: 10
    preferredHighlightBegin: 0.9
    preferredHighlightEnd: 1

    path: Path {
        startX: pageList.x + pageList.width*0.1
        startY: pageList.y + pageList.height*0.2

        PathQuad{
            x: pageList.width
            y: pageList.y + pageList.height*0.5
            controlX: pageList.width*0.5
            controlY: pageList.y + pageList.height
        }
    }
}
