import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtTelemetry 1.0

Item {
    anchors.fill: parent
    visible: AppController.appState.errorMessage.length > 0

    Rectangle {
        anchors.centerIn: parent
        width: 400
        height: 200
        radius: 8
        color: "#2b2b2b"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            Label {
                text: qsTr("Connection Error")
                font.bold: true
                color: "#ffffff"
            }

            Label {
                text: AppController.appState.errorMessage
                color: "#ff8a80"
                wrapMode: Text.WordWrap
            }

            Button {
                text: qsTr("Retry")
                onClicked: AppController.connectToServer("wss://echo.websocket.events")
            }
        }
    }

}
