#include "contextmenuwindow.h"

ContextMenuWindow::ContextMenuWindow(QWidget *parent)
    :QTextEdit(parent)
{
    menu = new QMenu(this);
    QAction* action_cpyText = menu->addAction(tr("Копировать формат текста"));
    QAction* action_applText = menu->addAction(tr("Применить формат текста"));

    connect(action_cpyText, &QAction::triggered, this, &ContextMenuWindow::copyTextFormat);
    connect(action_applText, &QAction::triggered, this, &ContextMenuWindow::applyTextFormat);
}

void ContextMenuWindow::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void ContextMenuWindow::copyTextFormat()
{
    ch_format = textCursor().charFormat(); //получаем формат выделенного текста
}

void ContextMenuWindow::applyTextFormat()
{
    if(ch_format.isCharFormat()){
        textCursor().setCharFormat(ch_format);
    }
}
