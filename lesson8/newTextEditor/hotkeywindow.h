#pragma once

#include <QWidget>

#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QEventLoop>

class HotKeyWindow: public QWidget
{
    Q_OBJECT

public:
    HotKeyWindow(QWidget* parent = nullptr);
    void setListCommand(qint8 idx, QString command);
    qint8 getListCommandIdx();
    void setKeyText(QString key_text);
    QPair<Qt::Key, Qt::KeyboardModifier> getCurrentPressedKey();

signals:
    void indexChanged();
    void editKey();
    void keyPressed();

private slots:
    void on_ChangeIndexList();
    void on_EditHotKey();

private:
    QGroupBox* pGroupBox;
    QComboBox* pListCommand;
    QLabel* lblKeysText;
    QLabel* lblSetKeys;
    QPushButton* btnEdit;
    QLabel* lblKeysName;

    QVBoxLayout *hbLayout;

    Qt::Key curPressKey;
    Qt::KeyboardModifier curPressMod;

protected:
    virtual void keyPressEvent(QKeyEvent* pEvent);
};
