import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtMultimedia 5.4
import OpenCV 1.0
import cn.chwangteng.Capture 1.0

Item {
    Capture{
        id:wtcapture
    }


    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100
            OpenCVcamera {
                id:opencvCamera
                m_cameraId: 0
                m_run: true
            }

            OpenCVshowFrameCapture {
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
//            VideoOutput{
//                Layout.fillHeight: true
//                Layout.fillWidth: true
//                source: main_camera
//                Camera{
//                    id:main_camera
//                }
//            }
        }

        ColumnLayout {
            id: columnLayout1
            width: 100
            height: 100

            Row {
                id: row
                width: 200
                height: 400

                Button {
                    id: button
                    text: qsTr("开始捕捉")
                    highlighted: true
                    onClicked: {
                        wtcapture.captureCallInQml()
                    }
                }

                Button {
                    id: mosaic
                    text: qsTr("马塞克")
                    highlighted: true
                    onClicked: {
                        opencvShowFrame.mosaic=!opencvShowFrame.mosaic
                        if(opencvShowFrame.mosaic)
                            mosaic.highlighted=true
                        else
                            mosaic.highlighted=false
                    }
                }
            }

            Label {
                id: label
                text: qsTr("捕捉到的人脸")
                Layout.fillHeight: false
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            }



            ListView {
                id: listView
                x: 0
                y: 0
                width: 110
                height: 160
                Layout.fillHeight: true
                Layout.fillWidth: false
                delegate: Item {
                    x: 5
                    width: 110
                    height: im.height+te.height*2
                    Column {
                        id: row1
                        Image {
                            id:im
                            source: model.imagepath
                            width: 80
                            height: 80
                            sourceSize.height: 80
                            sourceSize.width: 80
                        }

//                        Rectangle{
//                            color: colorCode
//                            width: 80
//                            height: 80
//                        }
                        Text {
                            id:te
                            text: "name"
                            font.bold: true
                        }
                        spacing: 10
                    }
                }
                model:myModel
            }


        }
    }
}
