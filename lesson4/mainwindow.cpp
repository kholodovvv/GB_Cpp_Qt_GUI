#include "mainwindow.h"

#include <QApplication>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QMdiSubWindow>
#include <QToolBar>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QEventLoop>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    translator.load(":/lang/QtLanguage_ru"); //Загрузка перевода по умолчанию
    qApp->installTranslator(&translator); //Устанавливаем перевод  по умолчанию
    language = "ru";

    MainWindow::setWindowTitle(":: New Text Editor ::"); //Название программы в заголовке окна
    QPair<QMdiSubWindow*, QString> chWindow;

    mdiArea = new QMdiArea(this); //создаём родительскую область для многооконного приложения

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget); //установка центрального дочернего окна
                              //(окно, которое создаётся по умолчанию вместе с родительской областью)
    QGridLayout *grdLayout = new QGridLayout(this); //создаём слой
    widget->setLayout(grdLayout); //устанавливаем виджету слой
    widget->setFixedSize(800, 600); //задаём фиксированный размер главного окна
    grdLayout->addWidget(mdiArea); //распологаем на слое родительскую область

    QPlainTextEdit* pTextEdit = new QPlainTextEdit(this); //создаём новый текстовый редактор
    pTextEdit->setAttribute(Qt::WA_DeleteOnClose); //виджет должен быть уничтожен при закрытии окна
    pTextEdit->setWindowTitle(tr("Новый документ")); //текст заголовка окна
    mdiArea->addSubWindow(pTextEdit); //помещаем дочернее окно с текстовым редатором в родительскую область
    mdiArea->tileSubWindows(); //упорядочиваем дочерние окна в виде плиток

    //создаём toolbar
    QToolBar* tb = addToolBar("MainToolbar");
    tb->setMovable(false);
    QAction* tbProhibitEditing = tb->addAction(QIcon(":/img/img/editing.png"), "");
    connect(tbProhibitEditing, &QAction::triggered, this, &MainWindow::on_ProhibitEditing);
    tb->addSeparator();
    QAction* tbNewDocument = tb->addAction(QIcon(":/img/img/ndoc.png"), "");
    connect(tbNewDocument, &QAction::triggered, this, &MainWindow::on_NewDocument);
    QAction* tbSave = tb->addAction(QIcon(":/img/img/save.png"), "");
    connect(tbSave, &QAction::triggered, this, &MainWindow::on_SaveDocument);
    QAction* tbOpen = tb->addAction(QIcon(":/img/img/open.png"), "");
    connect(tbOpen, &QAction::triggered, this, &MainWindow::on_OpenDocument);
    tb->addSeparator();
    QAction* tbChangeLanguage = tb->addAction(QIcon(":/img/img/lang.png"), "");
    connect(tbChangeLanguage, &QAction::triggered, this, &MainWindow::on_Change_Lenguage);
    QAction* tbHotKey = tb->addAction(QIcon(":/img/img/hatkey.png"), "");
    connect(tbHotKey, &QAction::triggered, this, &MainWindow::on_ChangeHotKeyWindow);
    QAction* tbExit = tb->addAction(QIcon(":/img/img/exit.png"), "");
    connect(tbExit, &QAction::triggered, this, &MainWindow::on_ExitProgram);

    //запись клавиш быстрого доступа по умолчанию
    Hotkey hot_key{};
    hot_key.command = tr("Сохранить");
    hot_key.key = Qt::Key_S;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 0;
    vecHotKey.push_back(hot_key);

    hot_key.command = tr("Открыть");
    hot_key.key = Qt::Key_O;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 1;
    vecHotKey.push_back(hot_key);

    hot_key.command = tr("Новый документ");
    hot_key.key = Qt::Key_N;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 2;
    vecHotKey.push_back(hot_key);

    hot_key.command = tr("Выход");
    hot_key.key = Qt::Key_Q;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 3;
    vecHotKey.push_back(hot_key);
}

void MainWindow::keyPressEvent(QKeyEvent* pEvent)
{
    qint8 idx;
    bool flag = false;

    for(auto it = vecHotKey.begin(); it != vecHotKey.end(); it++){
        if(pEvent->modifiers() == it->modifier && pEvent->key() == it->key){
            idx = it->idx;
            flag = true;
        }
    }

    if(flag){
        switch (idx) {
            case 0:
                on_SaveDocument();
            break;

            case 1:
                on_OpenDocument();
            break;

            case 2:
                on_NewDocument();
            break;

            case 3:
                on_ExitProgram();
            break;
        }
    }else{
        curPressedKey = Qt::Key(pEvent->key());

        switch (pEvent->modifiers()) {
            case Qt::ControlModifier:
                curTextPressedKey = "Ctrl + ";
                curPressedMod = Qt::ControlModifier;
            break;

            case Qt::AltModifier:
                curTextPressedKey = "Alt + ";
                curPressedMod = Qt::AltModifier;
            break;

            case Qt::ShiftModifier:
                curTextPressedKey = "Shift + ";
                curPressedMod = Qt::ShiftModifier;
            break;
        }

        curTextPressedKey.append(QChar(pEvent->key()));
    }

    emit keyPressed();
}

MainWindow::~MainWindow()
{
}

void MainWindow::SaveFile(const QString filename, QString filetext)
{
    QFile file(filename);
    QByteArray data;

    data.append(QString(filetext).toUtf8());

        if(file.open(QIODevice::WriteOnly)){
            file.write(data);
        }else{
            QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка записи в файл!"));
            return;
        }

    file.close();
}

void MainWindow::on_NewDocument()
{

    QPlainTextEdit* pTextEdit = new QPlainTextEdit(this); //создаём новый текстовый редактор
    pTextEdit->setReadOnly(true); //режим только для чтения
    pTextEdit->setAttribute(Qt::WA_DeleteOnClose); //виджет должен быть уничтожен при закрытии окна
    pTextEdit->setWindowTitle(tr("Новый документ"));
    mdiArea->addSubWindow(pTextEdit); //помещаем дочернее окно с текстовым редатором в родительскую область

    pTextEdit->show();
}

void MainWindow::on_SaveDocument()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QPlainTextEdit* textEdit = (QPlainTextEdit*)wdg;

    QString save_file_name;
    QPair<QMdiSubWindow*, QString> chWindow;

    for(auto it = vecDocuments.begin(); it != vecDocuments.end(); it++){
        if(it->first == subWindow){
            if(it->second.isEmpty()){
                save_file_name = QFileDialog::getSaveFileName(this, tr("Сохранить как"), QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

                if(!save_file_name.isEmpty()){
                    SaveFile(save_file_name, textEdit->toPlainText());

                    QFileInfo file_name(save_file_name);
                    subWindow->setWindowTitle(file_name.fileName());
                }
                return;
            }else{
                SaveFile(it->second, textEdit->toPlainText());
                return;
            }
        }
    }

    save_file_name = QFileDialog::getSaveFileName(this, tr("Сохранить как"), QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

    if(!save_file_name.isEmpty()){
        SaveFile(save_file_name, textEdit->toPlainText());

        QFileInfo file_name(save_file_name);
        subWindow->setWindowTitle(file_name.fileName());

        chWindow.first = subWindow;
        chWindow.second = save_file_name;
        vecDocuments.push_back(chWindow);
    }
}

QString MainWindow::ReadFile(const QString filename)
{
    QFile file(filename);
    QString textdata;

    if(file.open(QIODevice::ReadOnly)){
        textdata = file.readAll();
    }else{
        QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка открытия файла!"));
    }

    file.close();

    return textdata;
}

QString MainWindow::TextKey(qint8 idx)
{
    QString textHotKey;

    switch (vecHotKey.at(idx).modifier) {
        case Qt::ControlModifier:
            textHotKey = "Ctrl + ";
        break;

        case Qt::AltModifier:
            textHotKey = "Alt + ";
        break;

        case Qt::ShiftModifier :
            textHotKey = "Shift + ";
        break;
    }

    textHotKey.append(QChar(vecHotKey.at(idx).key));

    return textHotKey;
}

void MainWindow::on_OpenDocument()
{
    QString open_file_name;
    QPair<QMdiSubWindow*, QString> chWindow;

    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QPlainTextEdit* textEdit = (QPlainTextEdit*)wdg;

    for(auto it = vecDocuments.begin(); it != vecDocuments.end(); it++){
        if(it->first == subWindow){
            open_file_name = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

            if(!open_file_name.isEmpty()){
                textEdit->setPlainText(ReadFile(open_file_name));

                QFileInfo file_name(open_file_name);
                subWindow->setWindowTitle(file_name.fileName());
                it->second = open_file_name;
            }

         return;
        }
    }

    open_file_name = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), "Text(*.txt);;ALL(*.*)");

    if(!open_file_name.isEmpty()){
        textEdit->setPlainText(ReadFile(open_file_name));

        QFileInfo file_name(open_file_name);
        subWindow->setWindowTitle(file_name.fileName());

        chWindow.first = subWindow;
        chWindow.second = open_file_name;
        vecDocuments.push_back(chWindow);
    }
}

void MainWindow::on_ProhibitEditing()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QPlainTextEdit* textEdit = (QPlainTextEdit*)wdg;

    if(textEdit->isReadOnly()){
        textEdit->setReadOnly(false);
    }else{
        textEdit->setReadOnly(true);
    }

}

void MainWindow::on_ChangeHotKeyWindow()
{

    QString textHotKey; //текстовое представление горячей клавиши

    QGroupBox* pGroupBox = new QGroupBox;
    pGroupBox->setAttribute(Qt::WA_DeleteOnClose); //виджет должен быть уничтожен при закрытии окна
    pGroupBox->setWindowTitle(tr("Горячие клавиши"));

    QComboBox* pComboBox = new QComboBox;
    pComboBox->setObjectName("cmbSelectKey");

    for(auto it = vecHotKey.begin(); it != vecHotKey.end(); it++){
        pComboBox->insertItem(it->idx, it->command);
    }

    connect(pComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::on_ChangeIndexList);

    QLabel* lblKeysText = new QLabel(tr("Действие:"));
    QLabel* lblSetKeys = new QLabel(tr("Назначенные кнопки:"));
    QPushButton* btnEdit = new QPushButton(tr("Изменить"));
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::on_EditHotKey);

    QLabel* lblKeysName = new QLabel(TextKey(0));
    lblKeysName->setObjectName("lblKeys_Name");

    QVBoxLayout *hbLayout = new QVBoxLayout; //создаём слой
    pGroupBox->setLayout(hbLayout);

    hbLayout->addWidget(lblKeysText);
    hbLayout->addWidget(pComboBox);
    hbLayout->addWidget(lblSetKeys);
    hbLayout->addWidget(lblKeysName);
    hbLayout->addWidget(btnEdit);

    mdiArea->addSubWindow(pGroupBox); //помещаем дочернее окно с текстовым редатором в родительскую область

    pGroupBox->show();
}

void MainWindow::on_Change_Lenguage()
{
    if("ru" == language){
        translator.load(":/lang/QtLanguage_en"); //Загрузка перевода
        qApp->installTranslator(&translator); //Устанавливаем перевод
        language = "en";
    }else{
        translator.load(":/lang/QtLanguage_ru");
        qApp->installTranslator(&translator);
        language = "ru";
    }
}

void MainWindow::on_ExitProgram()
{
    MainWindow::close();
}

void MainWindow::on_ChangeIndexList()
{
    QComboBox *pComboBox = findChild<QComboBox*>("cmbSelectKey");
    QLabel *lblKeysName = findChild<QLabel*>("lblKeys_Name");

    lblKeysName->setText(TextKey(pComboBox->currentIndex()));
}

void MainWindow::on_EditHotKey()
{
    QLabel *lblKeysName = findChild<QLabel*>("lblKeys_Name");
    QComboBox *pComboBox = findChild<QComboBox*>("cmbSelectKey");

    lblKeysName->setText(tr("Жду нажатия кнопки ..."));

    QEventLoop loop;
        connect(this, &MainWindow::keyPressed, &loop, &QEventLoop::quit);
    loop.exec();

    lblKeysName->setText(curTextPressedKey);

    vecHotKey[pComboBox->currentIndex()].key = curPressedKey;
    vecHotKey[pComboBox->currentIndex()].modifier = curPressedMod;
}

