import QtQuick 2.12
import QtQuick.Controls 2.5
import "../qml/CustomComponents"

Frame{
    height: 230

    Column{
        anchors.fill: parent
        spacing: 5

        Text {
            id: title
            width: parent.width
            height: 50
            text: qsTr("Disk Scheduling Algorithm")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
        }

        Row{
            id: typeOfAlgorithm
            width: parent.width*0.9
            anchors.horizontalCenter: parent.horizontalCenter
            height: 35
            spacing: 10

            Text {
                text: qsTr("Select the algorithm to apply: ")
                width: parent.width*0.4
                height: parent.height
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
            }

            RComboBox{
                id: typeOfAlgorithmCb
                width: parent.width*0.6
                height: parent.height
                model: ["First In First Served (FIFS)", "Shortest Seek Time First (SSTF)"]
            }
        }

        Row{
            id: frameSize
            width: parent.width*0.9
            anchors.horizontalCenter: parent.horizontalCenter
            height: 35
            spacing: 10

            Text {
                text: qsTr("Enter Cylinder Size: ")
                width: parent.width*0.3
                height: parent.height
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
            }

            TextField{
                id: inputFrame
                width: parent.width*0.4
                height: parent.height
                validator: IntValidator{
                    bottom: 1
                    top: 3600
                }
                //onAccepted: demandPagingCPP.FrameSize = inputFrame.text
            }

            RTextButton{
                id: updateFrameSize
                width: parent.width*0.3
                height: parent.height
                text: "Update"
                //onClicked: demandPagingCPP.FrameSize = inputFrame.text
            }
        }

        Row{
            id: pageList
            width: parent.width*0.9
            anchors.horizontalCenter: parent.horizontalCenter
            height: 35
            spacing: 10

            Text {
                text: qsTr("Enter Another Page: ")
                font.pointSize: 12
                width: parent.width*0.3
                height: parent.height
                verticalAlignment: Text.AlignVCenter
            }

            TextField{
                id: inputPage
                width: parent.width*0.4
                height: parent.height
                validator: IntValidator{
                    bottom: 0
                    top: 100
                }
                onAccepted: {
                    demandPagingCPP.addPage(text)
                    text = ""
                }
            }

            RTextButton{
                id: pushPage
                width: parent.width*0.3
                height: parent.height
                text: "Add it"
                onClicked: {
                    demandPagingCPP.addPage(inputPage.text)
                    inputPage.text = ""
                }
            }
        }

        Row{
            id: controlBtns
            width: 150
            height: 35
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            RTextButton{
                width: 70
                height: parent.height
                text: "Start"
                onClicked: demandPagingCPP.startCalculation(typeOfAlgorithmCb.currentIndex)
            }

            RTextButton{
                width: 70
                height: parent.height
                text: "Reset"
                onClicked: {
                    inputFrame.text = ""
                    inputPage.text = ""
                    demandPagingCPP.reset()
                }
            }
        }
    }
}
