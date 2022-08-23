#include "fileviewwidget.h"

#include <QFile>
#include <QDir>
#include <QLabel>

FileViewWidget::FileViewWidget(QWidget *parent)
    : QWidget(parent), model(nullptr)
{
    gridLay = new QGridLayout(this); // создаем слой для компоновки
    this->setLayout(gridLay); // устанавливаем слой на виджет
    tree = new QTreeView(this);
    gridLay->addWidget(tree, 1, 0, 10, 10); // размещен на первой строке
                                            // с нулевого столбца
                                            // занимает 10 условных строк
                                            // и столбцов
    setMinimumSize(500, 600); // ограничиваем размер виджета

    if(QSysInfo::productType() == "windows")
    {
        disckSelBox = new QComboBox(this);
        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listdisk = list.begin();
        int amount = list.count();

        for (int i = 0; i < amount; i++)
        {
            disckSelBox->addItem(listdisk->path());
            listdisk++;
        }

        if (amount > 0)
        {
            rebuildModel(list.at(0).path());
        }

        gridLay->addWidget(disckSelBox, 0, 0, 1, 2); // координаты
        connect(disckSelBox, SIGNAL(activated(int)), this, SLOT(chgDisk(int)));

        textSearch = new QLineEdit(this);
        gridLay->addWidget(textSearch, 0, 2, 1, 5);
        btnSearch = new QPushButton(this);
        btnSearch->setText("Search");
        gridLay->addWidget(btnSearch, 0, 7, 1, 2);
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(findFileSlot()));
    } else {
        mainPath = new QPushButton(this);
        mainPath->setText("/");
        gridLay->addWidget(mainPath, 0, 0, 1, 2);
        connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
        rebuildModel("/");

        textSearch = new QLineEdit(this);
        gridLay->addWidget(textSearch, 0, 2, 1, 5);
        btnSearch = new QPushButton(this);
        btnSearch->setText("Search");
        gridLay->addWidget(btnSearch, 0, 7, 1, 2);
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(findFileSlot()));
    }

    connect(tree, &QTreeView::clicked, this, &FileViewWidget::chkDir);

    currentDir = new QStatusBar(this);
    gridLay->addWidget(currentDir, 11, 0, 1, 10);

    controllerl = new Controller(this);
    connect(controllerl, SIGNAL(changFindPath(QString)), this,
    SLOT(changStatusLabel(QString)));
}

void FileViewWidget::setNewModel(QStandardItemModel *newmodel)
{
    tree->setModel(newmodel);
    model = newmodel;
}

void FileViewWidget::rebuildModel(QString str)
{
    curretnPath = str;
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem*> items;
    items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), str));
    model->appendRow(items);

    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
    QStringList list = dir.entryList();
    int amount = list.count();

    QList<QStandardItem*>folders;

    for (int i = 0; i < amount; i++)
    {
        QStandardItem* f = new
        QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)),
        list.at(i));
        folders.append(f);
    }
        items.at(0)->appendRows(folders);
        dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);amount =
        list.count();
        QList<QStandardItem*>files;

    for (int i = 0; i < amount; i++)
    {
        QStandardItem* f = new
        QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),
        list.at(i));
        files.append(f);
    }

    items.at(0)->appendRows(files);
    setNewModel(model);

}

void FileViewWidget::chgDisk(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void FileViewWidget::goMainPath()
{
    rebuildModel("/");
}

void FileViewWidget::chkDir()
{
    currentDir->showMessage("Текущий каталог: " + model->data(tree->currentIndex()).toString());
}

void FileViewWidget::findFileSlot()
{
    QString linesearch = textSearch->text();
    if (linesearch.length() == 0) return;
    controllerl->startFind(disckSelBox->currentText(), linesearch);
}

void FileViewWidget::changStatusLabel(QString line)
{
    currentDir->showMessage(line);
}


