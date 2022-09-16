#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QKeyEvent>
#include <QTranslator>

#include "hotkeywindow.h"
#include "changethemewindow.h"
#include "contextmenuwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct Hotkey{
        QString command;
        Qt::Key key;
        Qt::KeyboardModifier modifier;
        qint8 idx;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SaveFile(const QString filename, QString filetext);
    QString ReadFile(const QString filename);
    QMdiArea* mdiArea;
    QVector<Hotkey> vecHotKey; //вектор для хранения горячих клавиш
    QVector<QPair<QMdiSubWindow*, QString>> vecDocuments; //вектор для хранения дочерних окон и пути к файлам
    QString language;
    QString TextKey(qint8 idx); //возвращает из вектора текстовое представление сохранённой комбинации клавишь по индексу
    QTranslator translator;
    HotKeyWindow* HKW;
    ChangeThemeWindow* CTW;
    QMenu* mainMenu; //Главное меню программы

private slots:
    void on_NewDocument();
    void on_SaveDocument();
    void on_OpenDocument();
    void on_ProhibitEditing();
    void on_ChangeHotKeyWindow();
    void on_Change_Lenguage();
    void on_ExitProgram();
    void on_ChangeIndexList();
    void on_EditHotKey();
    void on_ChangeThemeWindow();
    void on_ChangeTheme();
    void on_PrinterWindow();
    void on_FontWindow();
    void on_AlignTextLeft();
    void on_AlignTextCenter();
    void on_AlignTextRight();

signals:
    //void keyPressed();

protected:
    virtual void keyPressEvent(QKeyEvent* pEvent);
};
#endif // MAINWINDOW_H
