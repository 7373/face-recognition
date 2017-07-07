import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.0
import cn.chwangteng.Identify 1.0



Item {

    Identify{
        id:identifier
        onComplete: {
            iscalculating=false
            result=true
            label3.text=similarity
        }
    }

    property bool iscalculating: false
    property bool result: false

    RowLayout {
        id: rowLayout
        anchors.topMargin: 64
        anchors.rightMargin: 64
        anchors.fill: parent
        ColumnLayout {
            id: columnLayout
            width: parent.width/3
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                id: label
                text: qsTr("第一张图片")
            }

            Button {
                id: button
                text: qsTr("添加图片...")
                highlighted: true
                onClicked: fileDialog.open()
                FileDialog {
                    id: fileDialog
                    folder : pictureUrl
                    selectMultiple: false
                    title: qsTr("打开图片")
                    nameFilters: [qsTr("图片 (*.jpg *.png *.bmp)"), qsTr("所有文件 (*.*)")]
                    onAccepted: {
                        console.log("You chose: " + fileDialog.fileUrls)
                        image.source=fileDialog.fileUrl
                    }
                }
            }

            Image {
                id: image
                width: 400
                height: 400
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 400
                sourceSize.height: 400
                source: "../images/图片占位符.svg"
            }
        }

        ColumnLayout {
            id: columnLayout1
            width: parent.width/3
            height: 100
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                id: label1
                text: qsTr("第二张图片")
            }

            Button {
                id: button1
                text: qsTr("添加图片...")
                highlighted: true
                onClicked: fileDialog1.open()
                FileDialog {
                    id: fileDialog1
                    folder : pictureUrl
                    selectMultiple: false
                    title: qsTr("打开图片")
                    nameFilters: [qsTr("图片 (*.jpg *.png *.bmp)"), qsTr("所有文件 (*.*)")]
                    onAccepted: {
                        console.log("You chose: " + fileDialog1.fileUrls)
                        image1.source=fileDialog1.fileUrl
                    }
                }
            }

            Image {
                id: image1
                width: 400
                height: 400
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 400
                sourceSize.height: 400
                source: "../images/图片占位符.svg"
            }
        }

        ColumnLayout {
            id: columnLayout2
            width: parent.width/3
            height: 100
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                id: button2
                text: qsTr("对比")
                highlighted: true
                onClicked: {
                    iscalculating=true
                    result=false
                    identifier.identifyCallInQml(image.source,image1.source)
                }
            }

            Label {
                id: label2
                text: qsTr("相似度为")
                visible: result
            }

            Label {
                id: label3
                text: qsTr("92.3%")
                visible: result
            }

            BusyIndicator {
                id: busyIndicator
                visible: iscalculating
            }
        }
    }
}
