#include "faq_dialog.h"

FaqDialog::FaqDialog(QWidget *parent): QWidget(parent){

    //auto mainBox = new QVBoxLayout();
    auto plTextEdit = new QPlainTextEdit();
    auto cmdClose = new QPushButton("Закрыть");

    //connect(cmdClose, &QPushButton::clicked, this, &FaqDialog::close);


}

FaqDialog::~FaqDialog()
{

}
