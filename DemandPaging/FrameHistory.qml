import QtQuick 2.12
import QtQuick.Controls 2.5

Frame {
    id: frameHistory
    anchors.horizontalCenter: parent.horizontalCenter
    padding: 0

    ListView{
        id: frameHistoryListView
        anchors.fill: parent
        anchors.margins: 5
        model: demandPagingCPP.FrameHistory
        orientation: ListView.Horizontal
        clip: true

        delegate: Rectangle{
            height: parent.height
            width: height/frameListView.count
            color: "transparent"
            Column{
                anchors.fill: parent
                spacing: 3

                Text {
                    text: modelData.Header
                    width: parent.width
                    height: parent.height*0.1
                    font.pointSize: 12
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "red"
                }

                ListView{
                    id: frameListView
                    property int perFrameHeight: count == 0 ? 0 : height/count
                    height: parent.height*0.8 - 6
                    width: parent.width
                    model: modelData.Pages

                    delegate: Rectangle{
                        color: "transparent"
                        height: frameListView.perFrameHeight
                        width: height*0.75
                        anchors.horizontalCenter: parent.horizontalCenter
                        border.width: 1
                        border.color: "#0a80a8"

                        Image {
                            source: "/local/assets/page.svg"
                            sourceSize.width: parent.width*0.9
                            sourceSize.height: parent.height*0.9
                            anchors.centerIn: parent
                        }

                        Text {
                            text: modelData.Id
                            font.bold: true
                            verticalAlignment: Text.AlignVCenter
                            font.pointSize: 10
                            horizontalAlignment: Text.AlignHCenter
                            anchors.centerIn: parent
                            //color: "white"
                            width: parent.width*0.9
                            height: parent.height*0.9
                        }
                    }
                }

                Text {
                    text: modelData.Status
                    width: parent.width
                    height: parent.height*0.1
                    font.pointSize: 12
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "blue"
                }
            }
        }

        add: Transition{
            NumberAnimation{
                property: "x"
                from: frameHistory.width
                duration: 250
            }
        }
    }
}
