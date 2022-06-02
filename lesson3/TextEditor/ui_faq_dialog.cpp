#include "ui_faq_dialog.h"

FaqDialog::FaqDialog(QWidget *parent)
    : QWidget(parent)
    , uid(new Ui::FaqDialog)
{
    uid->setupUi(this);

    Q_INIT_RESOURCE(resources);
    ui->faqButton->setIconSize(QSize(48,48));
    ui->faqButton->setIcon(QPixmap(":/img/faq.png"));

}


void FaqDialog::on_pbtnClose_clicked()
{

}
