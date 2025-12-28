import QtQuick

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Qt Telemetry Dashboard")

    Shortcut {
        sequence: "Escape"
        onActivated: Qt.quit()
    }

    Shortcut {
        sequence: "Alt+Return"
        onActivated: mainWindow.visibility = mainWindow.visibility === Window.FullScreen ? Window.Windowed : Window.FullScreen
    }
}
