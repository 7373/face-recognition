import QtQuick 2.0
import QtQuick.Controls 2.1
import QtGamepad 1.0
import QtQuick.Layouts 1.3
import QtMultimedia 5.4

Item {
    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                id: label
                text: qsTr("跟踪到的人像")
            }

            ListView {
                id: listView
                x: 0
                y: 0
                width: 110
                height: 160
                Layout.fillHeight: false
                Layout.fillWidth: true
                orientation: ListView.Horizontal
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    Row {
                        id: row1
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                        }

                        Text {
                            text: name
                            anchors.verticalCenter: parent.verticalCenter
                            font.bold: true
                        }
                        spacing: 10
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
            }
            VideoOutput{
                Layout.fillHeight: true
                Layout.fillWidth: true
                source: main_camera
                Camera{
                    id:main_camera
                }
            }

        }

        ColumnLayout {
            id: columnLayout1
            width: 100
            height: 100

            Label {
                id: label1
                text: qsTr("捕捉名单")
            }

            ComboBox {
                id: comboBox
                model: [qsTr("普通市民"), qsTr("敏感人员"), qsTr("犯罪分子")]
            }
        }

    }

}
