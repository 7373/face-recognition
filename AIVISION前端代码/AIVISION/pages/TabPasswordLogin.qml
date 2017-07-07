import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1


Item {

    id: itemlogin
    //property alias user_imageHeight: user_image.height

    Timer {
        id:timer
        interval: 1300; running: false; repeat: false
        onTriggered:{
            login_progressBar.visible=false
            if((username.text=="admin")&&(password.text=="admin")){
                islogin=true
            }
            else{
                contentDialog.open()
            }
            button_password_login.text=qsTr("登录")
        }
    }




    function checklogin(){
        login_progressBar.visible=true
        button_password_login.text=qsTr("登录中...")
        timer.start()
    }

    ColumnLayout {
        id: columnLayout
        width: 300
        height: 120
        spacing: 5
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: false
            Layout.fillWidth: true

            Image {
                id: user_image
                width: 40
                height: 40
                sourceSize.height: 30
                sourceSize.width: 30
                visible: true
                Layout.fillWidth: false
                source: "../images/账号.svg"
            }

            TextField {
                id: username
                width: 180
                text: qsTr("")
                Layout.fillWidth: true
                font.capitalization: Font.MixedCase
                placeholderText: qsTr("账号")
                focus: true
            }
        }

        RowLayout {
            id: rowLayout1
            width: 100
            height: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true

            Image {
                id: image
                width: 40
                height: 40
                Layout.fillWidth: false
                sourceSize.height: 30
                sourceSize.width: 30
                source: "../images/密码.svg"
            }

            TextField {
                id: password
                text: qsTr("")
                Layout.fillWidth: true
                placeholderText: qsTr("密码")
            }
        }

        Button {
            id: button_password_login
            text: qsTr("登录")
            highlighted: true
            Layout.fillWidth: true
            onClicked: checklogin()
        }

        ProgressBar {
            id: login_progressBar
            indeterminate: true
            Layout.fillWidth: true
            value: 0.5
            visible: false
        }
    }


    Dialog {
        id: contentDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: Math.min(parent.width, parent.height) / 3 * 2
        contentHeight: fail_label.height
        //parent: ApplicationWindow.overlay

        modal: true
        title: qsTr("登录失败")
        standardButtons: Dialog.Ok

        Flickable {
            id: flickable
            clip: true
            anchors.fill: parent
            contentHeight: column.height

            Column {
                id: column
                spacing: 20
                width: parent.width

                Label {
                    id:fail_label
                    width: parent.width
                    text: qsTr("无法登陆，用户名与密码不匹配或网络连接失败。")
                    wrapMode: Label.Wrap
                }
            }

            ScrollIndicator.vertical: ScrollIndicator {
                parent: contentDialog.contentItem
                anchors.top: flickable.top
                anchors.bottom: flickable.bottom
                anchors.right: parent.right
                anchors.rightMargin: -contentDialog.rightPadding + 1
            }
        }
    }

}
