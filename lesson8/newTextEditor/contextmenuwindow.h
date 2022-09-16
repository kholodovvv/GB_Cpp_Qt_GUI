#pragma once

#include <QObject>
#include <QTextEdit>
#include <QMenu>
#include <QContextMenuEvent>
#include <QFont>
#include <QApplication>
#include <QClipboard>

class ContextMenuWindow: public QTextEdit
{
    Q_OBJECT

public:
    ContextMenuWindow(QWidget* parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent* event);

private:
    QMenu* menu;
    QTextCharFormat ch_format;

private slots:
    void copyTextFormat();
    void applyTextFormat();
};
