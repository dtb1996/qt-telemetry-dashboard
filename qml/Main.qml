import QtQuick
import QtTelemetryDashboard

Window {
    id: mainWindow
    width: 1000
    height: 600
    visible: true
    title: qsTr("Qt Telemetry Dashboard")

    DashboardScreen {
        anchors.fill: parent
        anchors.margins: 12
    }

    Shortcut {
        sequence: "Escape"
        onActivated: Qt.quit()
    }

    Shortcut {
        sequence: "Alt+Return"
        onActivated: mainWindow.visibility = mainWindow.visibility === Window.FullScreen ? Window.Windowed : Window.FullScreen
    }
}
