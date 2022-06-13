#include "hotkeywindow.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>


HotKeyWindow::HotKeyWindow(QWidget *parent) :
    QWidget(parent)
{
    /*QWidget* widget = new QWidget(this);
    widget->setWindowFlags (Qt::Tool | Qt::WindowStaysOnTopHint);
    widget->setWindowTitle(tr("Горячие клавиши"));*/

    //hbLayout = new QVBoxLayout(this); //создаём слой
    //HotKeyWindow::setLayout(hbLayout);
    //widget->setFixedSize(300, 200); //задаём фиксированный размер главного окна

    /*cmbSelectCommand = new QComboBox(this);
    for(auto it = MW->vecHotKey.begin(); it != MW->vecHotKey.end(); it++){
        cmbSelectCommand->insertItem(it->idx, it->command);
    }*/

    //connect(cmbSelectCommand, &QComboBox::currentIndexChanged, this, &MainWindow::on_ChangeListKeys);

    //lblKeysText = new QLabel("Назначенные кнопки:");
    //lblKeysText->setText(tr("Назначенные кнопки:"));
    //lblKeysName = new QLabel("");
    /*lblKeysName->setAccessibleName("KeysName");
    lblKeysName->setText("");*/

    /*hbLayout->addWidget(cmbSelectCommand);
    hbLayout->addWidget(lblKeysText);
    hbLayout->addWidget(lblKeysName);

    setLayout(hbLayout);*/ //устанавливаем виджету слой
}

HotKeyWindow::~HotKeyWindow()
{

}

/*void HotKeyWindow::keyPressEvent(QKeyEvent *pEvent)
{

}*/

/*void HotKeyWindow::setHotKeyVector(QVector<HotKeyWindow::Hotkey> vecHKey)
{
    vecHotKey = vecHKey;
}*/
