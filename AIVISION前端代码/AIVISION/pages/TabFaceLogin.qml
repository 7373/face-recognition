import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtMultimedia 5.4

Item {
    property bool isfacetabshow: false

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Timer {
            id:face_timer
                interval: 100; running: isfacetabshow; repeat: false
                onTriggered:{
                    facesuccessDialog.open()
                    progressBar.indeterminate=false
                    progressBar.value=1
                    hint_timer.start()
                }
        }
        Timer{
            id:hint_timer
            interval: 1000;running: false;repeat: false
            onTriggered: {
                facesuccessDialog.close()
                islogin=true;
                main_camera.stop()
            }
        }
        Dialog {
            id: facesuccessDialog
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            width: Math.min(parent.width, parent.height) / 3 * 2
            contentHeight: fail_label.height*2
            modal: true
            title: qsTr("识别成功")
                Column {
                    id: column
                    spacing: 20
                    width: parent.width
                    Label {
                        id:fail_label
                        width: parent.width
                        text: qsTr("你好，柴飞祥")
                        wrapMode: Label.Wrap
                    }
                }
        }

        ProgressBar {
            id: progressBar
            height: 4
            Layout.fillHeight: false
            scale: 1
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            indeterminate: true
            value: 0.5
        }

        Label {
            id: label
            color: "#2196f3"
            text: qsTr("正在识别你的面部...")
            font.bold: true
            font.pointSize: 14
            fontSizeMode: Text.FixedSize
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
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

}
