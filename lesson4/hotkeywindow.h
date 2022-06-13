#pragma once

#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QKeyEvent>


class HotKeyWindow: public QWidget
{
    Q_OBJECT

public:
    HotKeyWindow(QWidget* parent = nullptr);
    ~HotKeyWindow();

private:
    MainWindow* MW;
    QVBoxLayout *hbLayout;
    QComboBox *cmbSelectCommand;
    QLabel *lblKeysText;
    QLabel* lblKeysName;
/*protected:
    virtual void keyPressEvent(QKeyEvent* pEvent);*/
};
