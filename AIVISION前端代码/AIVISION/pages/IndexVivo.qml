import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtMultimedia 5.4
import QtQuick.Extras 1.4
import cn.chwangteng.VivoExpression 1.0
import OpenCV 1.0
import QtQuick.Dialogs 1.2

Item {

    VivoExpression{
        id:vivoExpre
         onHintChanged: {
             label1.text=hint
         }
    }

    Timer {
        id:face_timer
            interval: 100; running: true; repeat: true
            onTriggered:{
                statusIndicator.active=!statusIndicator.active
            }
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent


        OpenCVcamera {
            id:opencvCamera
            m_cameraId: 0
            m_run: true
        }

        OpenCVshowFrame {
            //anchors.centerIn: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
            anchors {left:parent.left; top:parent.top}
            id:opencvShowFrame
            m_capture: opencvCamera
            m_frameRate: 33
            m_run: true
            width: 330
            height: 430
        }


//        VideoOutput{
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//            source: main_camera
//            Camera{
//                id:main_camera
//            }
//        }

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100

            Label {
                id: label
                text: qsTr("提示")
            }

            StatusIndicator {
                id: statusIndicator
                color: "#00ff00"
                active: true
            }

            Label {
                id: label1
            }

            Button {
                id: button
                text: qsTr("模式1-视线追踪")
                highlighted: true
                onClicked: {

                }
            }

            Button {
                id: button1
                text: qsTr("模式2-表情识别")
                highlighted: true
                onClicked: {
                    vivoExpre.expressionCallInQml()
                }
            }
            MessageDialog {
                id: messageDialog
                title: qsTr("May I have your attention, please?")

                function show(caption) {
                    messageDialog.text = caption;
                    messageDialog.open();
                }
            }
        }
    }
}
