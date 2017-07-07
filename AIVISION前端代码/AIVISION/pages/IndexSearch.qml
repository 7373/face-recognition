import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.0
import cn.chwangteng.Search 1.0


Item {

    Search{
        id:search
        onComputeFinish: {
            console.log("searchcomputefinish")
            computingDialog.title=qsTr("与服务器通信中")
        }
        onComplete: {
            button.enabled=true
            busyindi.visible=false
            result.visible=true
            computingDialog.title=qsTr("完成")
            result.text=qsTr("已从人像库中找到结果")
            name.text=namestr
            code.text=codestr
            sex.text=sexstr
            type.text=typestr
            imageold.source=imagepathstr
        }
        onError: {
            button.enabled=true
            busyindi.visible=false
            result.visible=true
            computingDialog.title=qsTr("失败")
            result.text=qsTr("与服务器通信出错")
        }
    }



    RowLayout {
        id: rowLayout
        anchors.fill: parent

        Dialog {
            id: computingDialog
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            width: Math.min(parent.width, parent.height) / 3 * 2
            contentHeight: busyindi.height
            modal: true
            standardButtons: Dialog.Close | Dialog.Ok
            title: qsTr("图片处理中...")
                    BusyIndicator{
                        id:busyindi
                        x: (parent.width - width) / 2
                        y: (parent.height - height) / 2
                    }
                    Label{
                        id:result
                        x: (parent.width - width) / 2
                        y: (parent.height - height) / 2
                    }
        }


        ColumnLayout {
            id: columnLayout
            width: parent.width/3
            height: 100
            Layout.fillWidth: false
            Layout.fillHeight: true

            Label {
                id: label
                text: qsTr("请添加目标人像")
            }

            Button {
                id: button
                text: qsTr("打开图片...")
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
                sourceSize.height: 400
                sourceSize.width: 400
                Layout.fillWidth: true
                source: "../images/图片占位符.svg"
            }

            Button {
                id: button1
                width: parent.width
                text: qsTr("搜索")
                Layout.fillWidth: true
                onClicked: {
                    result.visible=false
                    busyindi.visible=true
                    computingDialog.title=qsTr("图像处理中...")
                    computingDialog.open()
                    search.searchCallInQml(image.source)
                }
            }
        }

        ColumnLayout {
            id: columnLayout1
            width: 100
            height: 100
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: text1
                text: qsTr("姓名")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: false
                font.pixelSize: 16
            }

            Text {
                id: name
                text: qsTr("姓名名称")
                font.family: "Courier"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 13
            }

            Text {
                id: text3
                text: qsTr("身份证号")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: code
                text: qsTr("身份证号号码")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 13
            }

            Text {
                id: text5
                text: qsTr("性别")
                font.family: "Arial"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: sex
                text: qsTr("男女")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }

            Text {
                id: text6
                text: qsTr("人员类别")
                font.family: "Arial"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: type
                text: qsTr("类别")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 12
            }

            Image {
                id: imageold
                width: 100
                height: 100
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                fillMode: Image.PreserveAspectFit
                Layout.fillHeight: true
                Layout.fillWidth: true
                source: "../images/图片占位符.svg"
            }
        }
    }
}
