import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "CustomComponents"

Popup {
    id: sidePanel
    property bool isExpanded: false
    property int normalizedWidth: 35
    property int widthWhenExpanded: 200

    padding: 0
    rightPadding: 1
    width: parent.width
    height: parent.height
    closePolicy: Popup.NoAutoClose

    Rectangle{
        id: sidePanelParentRect
        width: parent.width
        height: parent.height
        color: "#312d2d"

        Rectangle{
            anchors.fill: parent
            opacity: 0.2
            color: "lightgray"
        }

        Column{
            anchors.fill: parent
            spacing: 2

            RImageButton{
                id: hamburgerBtn
                width: normalizedWidth
                height: normalizedWidth
                icon.source: "/local/assets/icons-menu.svg"
                icon.color: "white"
                onClicked: {
                    isExpanded ? reverseExpandAnimation.start() : expandAnimation.start()
                    isExpanded = !isExpanded
                }
            }

            Column{
                width: parent.width
                height: normalizedWidth*3 + 6
                spacing: 2

                ButtonGroup{id: radioGroup}

                RImageExpandingButton{
                    id: demandPaging
                    width: parent.width
                    height: normalizedWidth
                    icon.source: "/local/assets/page-icon.svg"
                    text: "Demand Paging"
                    ButtonGroup.group: radioGroup
                    onClicked: mainTab.currentIndex = 0
                }

                RImageExpandingButton{
                    id: diskSchedular
                    width: parent.width
                    height: normalizedWidth
                    icon.source: "/local/assets/disk-icon.svg"
                    text: "Disk Scheduling"
                    ButtonGroup.group: radioGroup
                    onClicked: mainTab.currentIndex = 2
                }

                RImageExpandingButton{
                    id: cpuScheduling
                    width: parent.width
                    height: normalizedWidth
                    icon.source: "/local/assets/cpu-icon.svg"
                    text: "CPU Scheduler"
                    ButtonGroup.group: radioGroup
                    onClicked: mainTab.currentIndex = 1
                }

                RImageExpandingButton{
                    id: memoryAllocation
                    width: parent.width
                    height: normalizedWidth
                    icon.source: "/local/assets/ram-icon.svg"
                    text: "Memory Allocation"
                    ButtonGroup.group: radioGroup
                    onClicked: mainTab.currentIndex = 2
                }


            }
        }
    }

    PropertyAnimation{
        id: expandAnimation
        target: sidePanel
        property: "width"
        to: widthWhenExpanded
        duration: 200
    }

    PropertyAnimation{
        id: reverseExpandAnimation
        target: sidePanel
        property: "width"
        to: normalizedWidth
        duration: 200
    }

    Component.onCompleted: sidePanel.open()
}
