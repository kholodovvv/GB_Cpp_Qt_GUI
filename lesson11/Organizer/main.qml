import QtQuick 2.9
import QtQml 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import com.myinc.DataBase 1.0

Window {
    id: root
    visible: true
    width: 500
    height: 200
    title: qsTr("My Organizer")
    maximumHeight: 150
    minimumHeight: 150
    maximumWidth: 500
    minimumWidth: 500

    DataBase{
        id: db

        onLoadData: {

            tabmodel.append({date: dt, task: task, progress: prog})
        }
    }

    property var locale: Qt.locale()
    property date currentDate: new Date()
    property alias tabmodel: tabmodel

    Rectangle{
        width:parent.width
        height: parent.height
        anchors.fill: parent
        color: "grey"

        Text{
            id:lblTask
            width: 40
            height: 30
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 5
            anchors.leftMargin: 20
            text: "Task"
            color: "white"
        }

        Rectangle{
            id:rectTask
            anchors.left: lblTask.left
            anchors.top: lblTask.bottom
            width: 200
            height: 30
            color: "lightgrey"
            border.color: "grey"
            radius: 3

        TextEdit{
            id:txTask
            width: 200
            height: 30
            anchors.top: rectTask.top
            anchors.left: rectTask.left
            text: "New Task"
        }
        }

        Text{
            id:lblDate
            width: 40
            height: 30
            anchors.top: parent.top
            anchors.left: lblTask.right
            anchors.topMargin: 5
            anchors.leftMargin: txTask.width
            text: "Date"
            color: "white"
        }

        Rectangle{
            id:rectDate
            anchors.left: lblDate.left
            anchors.top: lblDate.bottom
            width: 80
            height: 30
            color: "lightgrey"
            border.color: "grey"
            radius: 3

        TextEdit{
            id:txDate
            width: 80
            height: 30
            anchors.top: rectDate.top
            anchors.left: rectDate.left
            text: { currentDate.toLocaleDateString(locale, Locale.ShortFormat) }
        }

        }

        Text{
            id:lblProgress
            width: 60
            height: 30
            anchors.top: parent.top
            anchors.left: lblDate.right
            anchors.topMargin: 5
            anchors.leftMargin: txDate.width
            text: "Progress"
            color: "white"
        }

        Slider{
            id:slProgress
            width: 80
            height: 30
            anchors.top: lblProgress.bottom
            anchors.left: lblProgress.left
            from: 0
            to: 10
            value: 0
            stepSize: 1
        }

        Text{
            id:lblValProgress
            width: 20
            height: 30
            anchors.top: lblProgress.bottom
            anchors.left: slProgress.right
            text: { slProgress.value }
            color: "white"
        }

        MyButton{
            id: btnAdd
            anchors.top: slProgress.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.topMargin: parent.height / 10
            onClicked: {
                var task = txTask.text;
                var datReg = new RegExp(/^(\d{1,2}).(\d{1,2}).(\d{4})$/);
                var dt = txDate.text;

                if(task.length < 1){
                    infMessage.text = "Поле Task не должно быть пустым!";
                    infMessage.open();
                    return;
                }else if(!datReg.test(dt) && dt.length < 10){
                    infMessage.text = "Поле Date некорректно заполнено!";
                    infMessage.open();
                    return;
                }else{

                    if(!db.insertRecord(txDate.text, txTask.text, slProgress.value)){
                        console.log("Запись не создана!");
                    }else{
                        tabmodel.append({date: txDate.text, task: txTask.text, progress: lblValProgress.text})
                    }
                }
            }
        }


        Rectangle{

            width: 60
            height: 40
            anchors.right: btnAdd.left
            anchors.rightMargin: 5
            anchors.topMargin: parent.height / 10
            anchors.top: slProgress.bottom
            color: "lightgrey"
            radius: 3

            MouseArea{
                anchors.fill: parent
                //onClicked: parent.clicked()
                onClicked: {
                    var component = Qt.createComponent("taskwindow.qml");
                    var window = component.createObject(root);
                    window.show();
                }
            }

            Text {
                text: "Tasks"
                color: "black"
                anchors.centerIn: parent
            }

        }

    }

    ListModel{
        id: tabmodel
        //ListElement{date: ""; task: ""; progress: ""}
    }

    MessageDialog{
        id: infMessage
        title: "Information Message"
        standardButtons: infMessage.Ok;
        onAccepted: infMessage.close();
    }


    Component.onCompleted: {
        if(!db.openDB("./db.db")){
            infMessage.text = "Ошибка соединения с БД!";
            infMessage.open();
        }else{
            db.readData();
        }

    }

}
