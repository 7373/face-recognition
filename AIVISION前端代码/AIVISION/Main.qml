import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "pages"

ApplicationWindow {
    visible: true
    width: 1240
    height: 680
    title: qsTr("AIVISION人脸识别系统")

    PageLogin{
            id:pagelogin
            anchors.fill: parent
            visible: !islogin
    }

    PageIndex{
        id:pageindex
        anchors.fill: parent
        visible: pagelogin.islogin
    }
}
