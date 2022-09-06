import QtQuick 2.0
import QtQml 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import com.myinc.DataBase 1.0

Window {
    id: root
    visible: true
    width: 500
    height: 200
    title: qsTr("My Tasks")
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 500
    minimumWidth: 500

    Rectangle{
        width:parent.width
        height: parent.height
        anchors.fill: parent
        color: "grey"

    TableView{
        id: tablView
        anchors.fill: parent
        model: tabmodel

        TableViewColumn{
            role: "date"
            title: "Дата"
        }

        TableViewColumn{
            role: "task"
            title: "Задача"
        }

        TableViewColumn{
            role: "progress"
            title: "Прогресс"
        }
    }


    }

    Connections{
        target: tabmodel
    }

}
