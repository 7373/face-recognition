import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.0
import cn.chwangteng.Register 1.0

Item {

    Register{
        id:regist
        onComputeFinish: {
            console.log("computefinish")
            computingDialog.title=qsTr("与服务器通信中")
        }
        onComplete: {
            button.enabled=true
            busyindi.visible=false
            result.visible=true
            computingDialog.title=qsTr("完成")
            result.text=qsTr("登记成功")
        }
        onError: {
            button.enabled=true
            busyindi.visible=false
            result.visible=true
            computingDialog.title=qsTr("失败")
            result.text=qsTr("与服务器通信出错")
        }
    }

    Dialog {
        id: computingDialog
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: Math.min(parent.width, parent.height) / 3 * 2
        contentHeight: busyindi.height
        modal: true
        standardButtons: Dialog.Close | Dialog.Ok
        title: qsTr("计算中...")

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
        anchors.rightMargin: 20
        anchors.fill: parent
        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Image {
                id: image
                width: 600
                height: 600
                Layout.fillHeight: true
                fillMode: Image.PreserveAspectFit
                sourceSize.height: 600
                sourceSize.width: 600
                Layout.fillWidth: true
                source: "../images/图片占位符.svg"
            }

            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100
                Layout.fillHeight: true
                Layout.fillWidth: true

                Button {
                    id: buttonAdd
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
                            image.source=fileDialog.fileUrl
                            console.log("You chose: " + fileDialog.fileUrl)
                        }
                    }
                }

                Label {
                    id: labelname
                    text: qsTr("姓名")
                }

                TextField {
                    id: textFieldname
                    placeholderText: qsTr("输入姓名")
                }

                Label {
                    id: labelsex
                    text: qsTr("性别")
                }

                ComboBox {
                    id: comboBoxsex
                    model: [qsTr("男"), qsTr("女")]

                }

                Label {
                    id: labelid
                    text: qsTr("身份证号")
                }

                TextField {
                    id: textFieldid
                    placeholderText: qsTr("18位身份证号")
                }

                Label {
                    id: labellabel
                    text: qsTr("人员类别")
                }

                ComboBox {
                    id: comboBoxlabel
                    model: [qsTr("普通市民"), qsTr("敏感人员"), qsTr("犯罪分子")]
                }

                RowLayout {
                    id: rowLayout1
                    width: 100
                    height: 100
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Button {
                        id: button
                        text: qsTr("录入")
                        checkable: false
                        highlighted: false
                        onClicked: {
                            button.enabled=false
                            computingDialog.open()
                            result.visible=false
                            busyindi.visible=true
                            computingDialog.title=qsTr("图像处理中...")
                            regist.registerCallInQml(image.source,
                                                      textFieldname.text,
                                                      comboBoxsex.currentText,
                                                      textFieldid.text,
                                                      comboBoxlabel.currentText)
                        }
                    }

                }
            }
        }
    }

}
