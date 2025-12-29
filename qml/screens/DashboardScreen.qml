import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtTelemetry 1.0
import "../components"

Rectangle {
    color: "#4c4c53"
    radius: 8

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        StatusBar {
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.leftMargin: 12
            Layout.rightMargin: 12
            spacing: 8

            Button {
                text: qsTr("Connect")
                enabled: !AppController.appState.connected
                onClicked: AppController.connectToServer("ws://localhost:8080")
            }

            Button {
                text: qsTr("Disconnect")
                enabled: AppController.appState.connected
                onClicked: AppController.disconnect();
            }

            BusyIndicator {
                running: AppController.appState.loading
                visible: running
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 6
            color: "#1e1e1e"

            ListView {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 6
                clip: true
                model: AppController.telemetryModel

                delegate: TelemetryCard {}
            }
        }
    }
}
