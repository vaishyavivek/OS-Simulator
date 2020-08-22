import QtQuick 2.12
import QtQuick.Controls 2.5

Frame{
    id: resultFrame

    Column{
        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        Text {
            text: qsTr("Page Faults Occured")
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width
            height: parent.height*0.18
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row{
            width: parent.width
            height: parent.height*0.1533
            spacing: 2

            TextField{
                width: parent.width*0.4
                height: parent.height
                readOnly: true
                text: demandPagingCPP.PageFaults
            }

            Text {
                text: qsTr("with ratio")
                font.pointSize: 8
                verticalAlignment: Text.AlignVCenter
                width: parent.width*0.25
                height: parent.height
            }

            TextField{
                width: parent.width*0.35 - 6
                height: parent.height
                readOnly: true
                text: demandPagingCPP.TotalPages == 0 ? 0 : (demandPagingCPP.PageFaults/demandPagingCPP.TotalPages).toPrecision(2)
            }
        }

        Text {
            text: qsTr("Page Hits Occured")
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width
            height: parent.height*0.18
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row{
            width: parent.width
            height: parent.height*0.1533
            spacing: 2

            TextField{
                width: parent.width*0.4
                height: parent.height
                readOnly: true
                text: demandPagingCPP.PageHits
            }

            Text {
                text: qsTr("with ratio")
                font.pointSize: 8
                verticalAlignment: Text.AlignVCenter
                width: parent.width*0.25
                height: parent.height
            }

            TextField{
                width: parent.width*0.35 - 6
                height: parent.height
                readOnly: true
                text: demandPagingCPP.TotalPages == 0 ? 0 : (demandPagingCPP.PageHits/demandPagingCPP.TotalPages).toPrecision(2)
            }
        }

        Text {
            text: qsTr("Of Total Pages Count")
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width
            height: parent.height*0.18
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField{
            width: parent.width*0.5
            height: parent.height*0.1533
            readOnly: true
            anchors.horizontalCenter: parent.horizontalCenter
            text: demandPagingCPP.TotalPages
        }
    }
}
