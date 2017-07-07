import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import cn.chwangteng.Quality 1.0

Item {
    property bool displayResult: false

    Quality{
        id:quality
        onComplete: {
            //对比度
            label11.text=contrast
            //清晰度
            label22.text=definition
            //亮度
            label33.text=brightnession

            displayResult=true
            button1.enabled=true
            button1.text=qsTr("检测")
        }
    }


    RowLayout {
        id: rowLayout
        anchors.rightMargin: 32
        anchors.fill: parent

        Image {
            id: image
            width: 100
            height: 100
            fillMode: Image.PreserveAspectFit
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: "../images/图片占位符.svg"
        }

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true

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
                        displayResult=false
                    }
                }
            }

            Button {
                id: button1
                text: qsTr("检测")
                onClicked: {
                    button1.text=qsTr("检测中")
                    displayResult=false
                    button1.enabled=false;
                    quality.qualityCallInQml(image.source)
                }
            }

            Label {
                id: label
                text: qsTr("检测结果:")
                visible: displayResult
            }
            Label {
                id: label1
                text: qsTr("对比度：")
                visible: displayResult
            }
            Label {
                id: label11
                text: quality.contrast
                visible: displayResult
            }
            Label {
                id: label2
                text: qsTr("清晰度：")
                visible: displayResult
            }
            Label {
                id: label22
                text: quality.definition
                visible: displayResult
            }
            Label {
                id: label3
                text: qsTr("亮度：")
                visible: displayResult
            }
            Label {
                id: label33
                text: quality.brightnession
                visible: displayResult
            }
//            Label {
//                id: label4
//                text: qsTr("人脸大小：")
//                visible: displayResult
//            }
//            Label {
//                id: label44
//                text: qsTr("30%")
//                visible: displayResult
//            }
//            Label {
//                id: label5
//                text: qsTr("人脸位置：")
//                visible: displayResult
//            }
//            Label {
//                id: label55
//                text: qsTr("30%")
//                visible: displayResult
//            }
//            Label {
//                id: label6
//                text: qsTr("人脸角度：")
//                visible: displayResult
//            }
//            Label {
//                id: label66
//                text: qsTr("XYZ")
//                visible: displayResult
//            }
        }
    }
}
