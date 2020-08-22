import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.12
import "../DemandPaging"
import "../CpuScheduler"
import "../MemoryAllocation"
import "../DiskSchedular"

ApplicationWindow{
    id: mainWindow
    visible: true
    minimumWidth: 900
    minimumHeight: 600
    //color: "#312d2d"

    property int opType: 0

    Image {
        width: parent.width
        height: parent.height
        sourceSize.width: width
        sourceSize.height: height
        opacity: 0.5
        source: "/local/assets/google-material-design-wallpaper-2.jpg"
    }

    Row{
        anchors.fill: parent
        Rectangle{
            id: sideBar
            width: 35
            height: parent.height
            color: "transparent"
            SidePanel{}
        }

        TabView{
            id: mainTab
            width: parent.width - sideBar.width
            height: parent.height
            currentIndex: 0
            tabsVisible: false

            Image {
                id: bg
                width: parent.width
                height: parent.height
                sourceSize.width: width
                sourceSize.height: height
                visible: false
                source: "/local/assets/google-material-design-wallpaper-2.jpg"
            }

            FastBlur{
                anchors.fill: bg
                source: bg
                opacity: 0.3
                radius: 32
            }

            Tab{
                title: "demandPaging"
                DemandPaging{
                    width: mainTab.width
                    height: mainTab.height
                }
            }

            Tab{
                title: "diskScheduling"
                DiskSchedular{
                    width: mainTab.width
                    height: mainTab.height
                }
            }

            Tab{
                title: "cpuScheduler"
                CpuScheduler{
                    width: mainTab.width
                    height: mainTab.height
                }
            }

            Tab{
                title: "memoryAllocation"
                MemoryAllocation{
                    width: mainTab.width
                    height: mainTab.height
                }
            }
        }
    }
}
