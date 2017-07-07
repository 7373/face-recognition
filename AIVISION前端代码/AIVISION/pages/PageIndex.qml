import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

Item {
    id: item1

    Loader{
        id:mainLoader
        anchors.leftMargin: 90
        anchors.fill: parent
        source:"IndexRegistration.qml"
    }


    ListView {
        id: listView
        spacing: 5
        width: 80
        flickableDirection: Flickable.AutoFlickDirection
        layoutDirection: Qt.LeftToRight
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        delegate: ItemDelegate {
            x: 5
            width: 80
            height: 80
            highlighted: listView.currentIndex===model.order
            onClicked: {
                mainLoader.source=model.qmlPath
                listView.currentIndex=model.order
                console.log(listView.currentIndex)
            }
                Rectangle{
                    width: 80
                    height: 70
                    color: "transparent"
                    Column {
                        id: row1
                        spacing: 10
                    Image {
                        width: 40
                        height: 40
                        source: model.imagePath
                    }
                    Text {
                        text: name
                        font.bold: true
                    }
                }
            }
        }
        model: ListModel {
            ListElement {
                name: qsTr("登记入库")
                imagePath: qsTr("../images/登记入库.svg")
                qmlPath:"IndexRegistration.qml"
                order:1
            }

            ListElement {
                name: qsTr("人脸检索")
                imagePath: qsTr("../images/人脸检索.svg")
                qmlPath:"IndexSearch.qml"
                order:2
            }

            ListElement {
                name: qsTr("人脸对比")
                imagePath: qsTr("../images/人脸对比.svg")
                qmlPath:"IndexIdentification.qml"
                order:3
            }

//            ListElement {
//                name: qsTr("真人鉴别")
//                imagePath: qsTr("../images/真人鉴别.svg")
//                qmlPath:"IndexVivo.qml"
//                order:4
//            }
            ListElement {
                name: qsTr("人脸捕获")
                imagePath: qsTr("../images/人脸捕获.svg")
                qmlPath:"IndexCapture.qml"
                order:5
            }
            ListElement {
                name: qsTr("人脸跟踪")
                imagePath: qsTr("../images/人脸跟踪.svg")
                qmlPath:"IndexTrack.qml"
                order:6
            }
            ListElement {
                name: qsTr("图像质量")
                imagePath: qsTr("../images/图像质量.svg")
                qmlPath:"IndexQuality.qml"
                order:7
            }
            ListElement {
                name: qsTr("设置")
                imagePath: qsTr("../images/设置.svg")
                qmlPath:"IndexSettings.qml"
                order:8
            }
        }
    }
}
