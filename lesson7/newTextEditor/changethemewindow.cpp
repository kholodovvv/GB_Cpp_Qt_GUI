#include "changethemewindow.h"

ChangeThemeWindow::ChangeThemeWindow(QWidget *parent)
    :QWidget(parent)
{
    pGrpBox = new QGroupBox(this);
    pGrpBox->setAttribute(Qt::WA_DeleteOnClose);
    pGrpBox->resize(300, 100);

    pCmbBox = new QComboBox(this);
    lblText = new QLabel(this);
    lblText->setText(tr("Темы оформления:"));

    pCmbBox->addItem(tr("Тёмная тема"));
    pCmbBox->addItem(tr("Зелёная тема"));

    btnEditTheme = new QPushButton(tr("Изменить тему"));
    connect(btnEditTheme, &QPushButton::clicked, this, &ChangeThemeWindow::on_ChangeTheme);

    hLayout = new QVBoxLayout(this);
    pGrpBox->setLayout(hLayout);

    hLayout->addWidget(lblText);
    hLayout->addWidget(pCmbBox);
    hLayout->addWidget(btnEditTheme);
}

qint8 ChangeThemeWindow::getThemeIdx()
{
    return pCmbBox->currentIndex();
}

void ChangeThemeWindow::on_ChangeTheme()
{
    emit change_theme();
}
