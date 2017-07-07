import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1

    property bool islogin: false

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        SwipeView {
            id: swipeView
            height: 480
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: true
            currentIndex: tabBar.currentIndex

            TabFaceLogin {
                isfacetabshow: tabBar.currentIndex==0
            }
            TabPasswordLogin{

            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            currentIndex: swipeView.currentIndex
            TabButton {
                text: qsTr("刷脸登录")

            }
            TabButton {
                text: qsTr("传统密码")
            }
        }
    }
}
