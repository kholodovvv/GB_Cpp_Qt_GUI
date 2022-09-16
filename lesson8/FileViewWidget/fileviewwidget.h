#ifndef FILEVIEWWIDGET_H
#define FILEVIEWWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStatusBar>
#include <QStandardItemModel>
#include <QLineEdit>
#include "Controller.h"
#include <QApplication>

Q_PROPERTY(QStandardItemModel *model READ getCurrentModel WRITE setNewModel)

class FileViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileViewWidget(QWidget *parent = nullptr);
    //~FileViewWidget();
    void clearTree();
    QStandardItemModel *getCurrentModel()const
    {
    return model;
    }
    void setNewModel(QStandardItemModel *newmodel);
    void rebuildModel(QString str);

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QPushButton *mainPath;
    QComboBox *disckSelBox;
    QStatusBar *currentDir;
    QLineEdit *textSearch;
    QPushButton *btnSearch;
    Controller *controllerl;

private slots:
    void chgDisk(int index); // получаем индекс выбранного диска
    void goMainPath(); // Для UNIX-подобных ОС верхним уровнем является путь /
    void chkDir();
    void findFileSlot();
    void changStatusLabel(QString);

private:
    QStandardItemModel *model;
    QString curretnPath;

};
#endif // FILEVIEWWIDGET_H
