import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    width: ListView.view.width
    height: 64
    radius: 6
    color: "#2b2b2b"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 12

        ColumnLayout {
            Layout.fillWidth: true

            Label {
                text: model.type + " (" + model.id + ")"
                color: "#ffffff"
                font.bold: true
            }

            Label {
                text: model.timestamp
                color: "#bbbbbb"
                font.pixelSize: 12
            }
        }

        Label {
            text: model.value.toFixed(2)
            color: "#ffffff"
            font.pixelSize: 20
        }

        Label {
            text: model.status
            color: model.status === "ok" ? "#81c784" : "#e57373"
            font.bold: true
        }
    }
}
