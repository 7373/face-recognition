import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Item {

    Settings {
        id: settings
        property string style: "刷脸登录"
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
            RowLayout {
                id: rowLayout
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillHeight: false
                Layout.fillWidth: true

                Label {
                    id: label
                    text: qsTr("登录方式")
                    font.capitalization: Font.SmallCaps
                    Layout.fillWidth: true
                    rightPadding: 0
                    bottomPadding: 0
                    padding: 0
                    Layout.rowSpan: 1
                    leftPadding: 0
                    font.wordSpacing: 5
                    topPadding: 0
                    font.pointSize: 14
                }

                ComboBox {
                    id: comboBox
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    model: ["刷脸登录","账号登录"]
                }
            }
    }
}
