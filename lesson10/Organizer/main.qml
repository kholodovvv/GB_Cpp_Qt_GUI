import QtQuick 2.9
import QtQml 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import com.myinc.FileReader 1.0

Window {
    id: root
    visible: true
    width: 500
    height: 200
    title: qsTr("My Organizer")
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 500
    minimumWidth: 500

    FileReader{
        id: fr

        onLoadData: {
            lstTaskModel.append({line: str});
        }
    }

    property var locale: Qt.locale()
    property date currentDate: new Date()

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
                    lstTaskModel.append({line: " " + txDate.text + " " +txTask.text + " " + lblValProgress.text});
                    fr.addRecord(txTask.text, txDate.text, lblValProgress.text)
                }
            }
        }

        Rectangle{
            id: rectLstTask
            width: parent.width - 10
            height: parent.height / 2
            anchors.top: btnAdd.bottom
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.topMargin: 5
            color: "lightgrey"
            border.color: "grey"
            radius: 3

            ListView{
                id: lstTask
                anchors.fill: parent
                model: lstTaskModel

                delegate:
                    Text{
                        text: line
                     }

            }
        }

        ListModel{
            id: lstTaskModel
            ListElement{line: ""}
        }

    }

    MessageDialog{
        id: infMessage
        title: "Information Message"
        standardButtons: infMessage.Ok;
        onAccepted: infMessage.close();
    }

    Component.onCompleted: fr.readFile() //загрузка данных при запуске приложения

}
