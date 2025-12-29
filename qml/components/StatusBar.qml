import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtTelemetry 1.0

Rectangle {
    height: 40
    radius: 6
    color: AppController.appState.connected ? "#2e7d32" : "#424242"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 8

        Label {
            text: AppController.appState.connected ? qsTr("Connected") : qsTr("Disconnected")
            color: "#ffffff"
            font.bold: true
        }

        Item { Layout.fillWidth: true }

        Label {
            visible: AppController.appState.errorMessage.length > 0
            text: AppController.appState.errorMessage
            color: "#ffccbc"
            elide: Text.ElideRight
        }
    }
}
