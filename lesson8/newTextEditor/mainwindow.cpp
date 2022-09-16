#include "mainwindow.h"

#include <QApplication>
#include <QGridLayout>
#include <QTextEdit>
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
#include <QMenu>
#include <QMenuBar>
#include <QPrintDialog>
#include <QPrinter>
#include <QFont>
#include <QFontDialog>
#include <QTextDocumentFragment>
#include <QTextDocument>
#include <QTextCursor>

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

    QTextEdit* pTextEdit = new ContextMenuWindow(this); //создаём новый текстовый редактор
    pTextEdit->setAttribute(Qt::WA_DeleteOnClose); //виджет должен быть уничтожен при закрытии окна
    pTextEdit->setWindowTitle(tr("Новый документ")); //текст заголовка окна
    mdiArea->addSubWindow(pTextEdit); //помещаем дочернее окно с текстовым редатором в родительскую область
    //mdiArea->addSubWindow(new ContextMenuWindow(this)); //подключаем контекстное меню
    mdiArea->tileSubWindows(); //упорядочиваем дочерние окна в виде плиток

    //Создаём выпадающее меню
    mainMenu = menuBar()->addMenu(tr("Файл"));
    QAction* menuNewDocument = mainMenu->addAction(tr("Создать"));
    connect(menuNewDocument, &QAction::triggered, this, &MainWindow::on_NewDocument);
    QAction* menuOpenDocument = mainMenu->addAction(tr("Открыть"));
    connect(menuOpenDocument, &QAction::triggered, this, &MainWindow::on_OpenDocument);
    QAction* menuSaveDocument = mainMenu->addAction(tr("Сохранить"));
    connect(menuSaveDocument, &QAction::triggered, this, &MainWindow::on_SaveDocument);
    QAction* menuPrintDocument = mainMenu->addAction(tr("Печать"));
    connect(menuPrintDocument, &QAction::triggered, this, &MainWindow::on_PrinterWindow);
    mainMenu->addSeparator();
    QAction* menuExitProgram = mainMenu->addAction(tr("Выход"));
    connect(menuExitProgram, &QAction::triggered, this, &MainWindow::on_ExitProgram);

    mainMenu = menuBar()->addMenu(tr("Настройки"));
    QAction* menuChangeLang = mainMenu->addAction(tr("Сменить язык"));
    connect(menuChangeLang, &QAction::triggered, this, &MainWindow::on_Change_Lenguage);
    QAction* menuChangeTheme = mainMenu->addAction(tr("Сменить оформление"));
    connect(menuChangeTheme, &QAction::triggered, this, &MainWindow::on_ChangeThemeWindow);
    QAction* menuHotKey = mainMenu->addAction(tr("Горячие клавиши"));
    connect(menuHotKey, &QAction::triggered, this, &MainWindow::on_ChangeHotKeyWindow);

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
    QAction* tbFont = tb->addAction(QIcon(":/img/img/font.png"), "");
    connect(tbFont, &QAction::triggered, this, &MainWindow::on_FontWindow);
    QAction* tbPrint = tb->addAction(QIcon(":/img/img/printer.png"), "");
    connect(tbPrint, &QAction::triggered, this, &MainWindow::on_PrinterWindow);
    tb->addSeparator();
    QAction* tbAlignTextLeft = tb->addAction(QIcon(":/img/img/text-left.png"), "");
    connect(tbAlignTextLeft, &QAction::triggered, this, &MainWindow::on_AlignTextLeft);
    QAction* tbAlignTextCenter = tb->addAction(QIcon(":/img/img/text-center.png"), "");
    connect(tbAlignTextCenter, &QAction::triggered, this, &MainWindow::on_AlignTextCenter);
    QAction* tbAlignTextRight = tb->addAction(QIcon(":/img/img/text-right.png"), "");
    connect(tbAlignTextRight, &QAction::triggered, this, &MainWindow::on_AlignTextRight);
    tb->addSeparator();
    QAction* tbChangeLanguage = tb->addAction(QIcon(":/img/img/lang.png"), "");
    connect(tbChangeLanguage, &QAction::triggered, this, &MainWindow::on_Change_Lenguage);
    QAction* tbHotKey = tb->addAction(QIcon(":/img/img/hatkey.png"), "");
    connect(tbHotKey, &QAction::triggered, this, &MainWindow::on_ChangeHotKeyWindow);
    tb->addSeparator();
    QAction* tbThemes = tb->addAction(QIcon(":/img/img/themes.png"), "");
    connect(tbThemes, &QAction::triggered, this, &MainWindow::on_ChangeThemeWindow);
    tb->addSeparator();
    QAction* tbDateTime = tb->addAction(QIcon(":/img/img/watch.png"), "");
    connect(tbDateTime, &QAction::triggered, this, &MainWindow::on_PasteDateTime);
    tb->addSeparator();
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

    hot_key.command = tr("Печать");
    hot_key.key = Qt::Key_P;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 3;
    vecHotKey.push_back(hot_key);

    hot_key.command = tr("Выход");
    hot_key.key = Qt::Key_Q;
    hot_key.modifier = Qt::ControlModifier;
    hot_key.idx = 4;
    vecHotKey.push_back(hot_key);
}

void MainWindow::keyPressEvent(QKeyEvent* pEvent)
{
    qint8 idx = -1;

    for(auto it = vecHotKey.begin(); it != vecHotKey.end(); it++){
        if(pEvent->modifiers() == it->modifier && pEvent->key() == it->key){
            idx = it->idx;
        }
    }

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
                on_PrinterWindow();
            break;

            case 4:
                on_ExitProgram();
            break;
        }
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

    QTextEdit* pTextEdit = new ContextMenuWindow(this); //создаём новый текстовый редактор
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
    QTextEdit* textEdit = (QTextEdit*)wdg;

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
    QTextEdit* textEdit = (QTextEdit*)wdg;

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
    QTextEdit* textEdit = (QTextEdit*)wdg;

    if(textEdit->isReadOnly()){
        textEdit->setReadOnly(false);
    }else{
        textEdit->setReadOnly(true);
    }

}

void MainWindow::on_ChangeHotKeyWindow()
{
    //создаём окно изменения горячих клавиш
    HKW = new HotKeyWindow();
    HKW->setWindowTitle(tr("Горячие клавиши"));

    connect(HKW, &HotKeyWindow::indexChanged, this, &MainWindow::on_ChangeIndexList);
    connect(HKW, &HotKeyWindow::editKey, this, &MainWindow::on_EditHotKey);

    for(auto it = vecHotKey.begin(); it != vecHotKey.end(); it++){
        HKW->setListCommand(it->idx, it->command);
    }

    HKW->setKeyText(TextKey(0));

    HKW->show();
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
    HKW->setKeyText(TextKey(HKW->getListCommandIdx()));
}

void MainWindow::on_EditHotKey()
{
    QPair<Qt::Key, Qt::KeyboardModifier> pressedKey = HKW->getCurrentPressedKey();

    vecHotKey[HKW->getListCommandIdx()].key = pressedKey.first;
    vecHotKey[HKW->getListCommandIdx()].modifier = pressedKey.second;
}

void MainWindow::on_ChangeThemeWindow()
{
    //создаём окно выбора темы
    CTW = new ChangeThemeWindow();
    CTW->setWindowTitle(tr("Темы оформления"));

    connect(CTW, &ChangeThemeWindow::change_theme, this, &MainWindow::on_ChangeTheme);

    CTW->show();
}

void MainWindow::on_ChangeTheme()
{
    qint8 idx;

    idx = CTW->getThemeIdx();

    switch (idx) {
        case 0: //Тёмная тема
            qApp->setStyleSheet("QMainWindow{background-color:black} QToolBar{background-color:grey}"
                                "QPlainTextEdit{background-color:grey} QComboBox{background-color:grey}"
                                "QGroupBox{background-color:black} QLabel{background-color:black; color:white}"
                                "QPushButton{background-color:grey}");
        break;

        case 1: //Зелёная тема
        qApp->setStyleSheet("QMainWindow{background-color:green} QToolBar{background-color:green}"
                            "QPlainTextEdit{background-color:green} QComboBox{background-color:green}"
                            "QGroupBox{background-color:green} QLabel{background-color:green; color:black}"
                            "QPushButton{background-color:grey}");
        break;
    }
}

void MainWindow::on_PrinterWindow()
{
    //Создания диалога вывода на печать
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Печать"));
    if (dlg.exec() != QDialog::Accepted)
    return;

    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;
    textEdit->print(&printer);
}

void MainWindow::on_FontWindow()
{
    //Создания диалога выбора шрифта
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;

    QFont font = textEdit->textCursor().charFormat().font(); //получаем текущий шрифт
    QFontDialog fntDlg(font,this);

    bool b[] = {true};
    font = fntDlg.getFont(b); // Запускаем диалог настройки шрифта

    if (b[0]){ // Если нажата кнопка OK, применяем новые настройки шрифта
        QTextCharFormat fmt;
        fmt.setFont(font);
        textEdit->textCursor().setCharFormat(fmt);
    }
}

//выравнивание текста по левому краю
void MainWindow::on_AlignTextLeft()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;

    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();

    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);

}

void MainWindow::on_AlignTextCenter()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;

    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();

    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}

void MainWindow::on_AlignTextRight()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;

    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();

    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    textEdit->setTextCursor(cursor);
}

void MainWindow::on_PasteDateTime()
{
    QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
    QWidget* wdg = subWindow->widget();
    QTextEdit* textEdit = (QTextEdit*)wdg;

    QTextCursor cursor = textEdit->textCursor();

    QDateTime dt = QDateTime::currentDateTime();
    QString datetime = "[" + dt.currentDateTime().toString() + "]";

    textEdit->textCursor().insertText(datetime);
}

