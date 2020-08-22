import QtQuick 2.12

ListView{
    id: frameListView
    model: demandPagingCPP.FrameList
    clip: true

    delegate: Rectangle{
        color: "transparent"
        height: pageHeight
        width: height*0.75
        border.width: 1
        border.color: "#0a80a8"

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
            font.pointSize: 16
            //color: "white"
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            width: parent.width*0.9
            height: parent.height*0.9
        }
    }
}
