#include "hotkeywindow.h"

HotKeyWindow::HotKeyWindow(QWidget *parent): QWidget(parent)
{
    pGroupBox = new QGroupBox(this);
    pGroupBox->setAttribute(Qt::WA_DeleteOnClose); //виджет должен быть уничтожен при закрытии окна
    pGroupBox->resize(300, 150);

    pListCommand = new QComboBox(this);

    connect(pListCommand, &QComboBox::currentIndexChanged, this, &HotKeyWindow::on_ChangeIndexList);

    lblKeysText = new QLabel(tr("Действие:"));
    lblSetKeys = new QLabel(tr("Назначенные кнопки:"));
    btnEdit = new QPushButton(tr("Изменить"));
    connect(btnEdit, &QPushButton::clicked, this, &HotKeyWindow::on_EditHotKey);

    lblKeysName = new QLabel("");

    hbLayout = new QVBoxLayout; //создаём слой
    pGroupBox->setLayout(hbLayout);

    hbLayout->addWidget(lblKeysText);
    hbLayout->addWidget(pListCommand);
    hbLayout->addWidget(lblSetKeys);
    hbLayout->addWidget(lblKeysName);
    hbLayout->addWidget(btnEdit);
}

void HotKeyWindow::setListCommand(qint8 idx, QString command)
{
    pListCommand->insertItem(idx, command);
}

qint8 HotKeyWindow::getListCommandIdx()
{
    return pListCommand->currentIndex();
}

void HotKeyWindow::setKeyText(QString key_text)
{
    lblKeysName->setText(key_text);
}

QPair<Qt::Key, Qt::KeyboardModifier> HotKeyWindow::getCurrentPressedKey()
{
    QPair<Qt::Key, Qt::KeyboardModifier> cPressKey;
    cPressKey.first = curPressKey;
    cPressKey.second = curPressMod;

    return cPressKey;
}

void HotKeyWindow::on_ChangeIndexList()
{
    emit indexChanged();
}

void HotKeyWindow::on_EditHotKey()
{
    setKeyText(tr("Жду нажатия кнопки ..."));

    QEventLoop loop;
        connect(this, &HotKeyWindow::keyPressed, &loop, &QEventLoop::quit);
    loop.exec();

    emit editKey();
}

void HotKeyWindow::keyPressEvent(QKeyEvent *pEvent)
{
    QString curTextPressedKey;

    curPressKey = Qt::Key(pEvent->key());

        switch (pEvent->modifiers()) {
            case Qt::ControlModifier:
                curTextPressedKey = "Ctrl + ";
                curPressMod = Qt::ControlModifier;
            break;

            case Qt::AltModifier:
                curTextPressedKey = "Alt + ";
                curPressMod = Qt::AltModifier;
            break;

            case Qt::ShiftModifier:
                curTextPressedKey = "Shift + ";
                curPressMod = Qt::ShiftModifier;
            break;
        }

   curTextPressedKey.append(QChar(pEvent->key()));
   HotKeyWindow::setKeyText(curTextPressedKey);

   emit keyPressed();
}
