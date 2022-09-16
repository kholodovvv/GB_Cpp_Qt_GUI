import QtQuick 2.2

    Rectangle{
        signal clicked()

        width: 60
        height: 40
        color: "lightgreen"
        radius: 3

        MouseArea{
            anchors.fill: parent
            onClicked: parent.clicked()
        }

        Text {
            text: "Add"
            color: "black"
            anchors.centerIn: parent
        }
    }

