#ifndef UI_FAQ_DIALOG_H
#define UI_FAQ_DIALOG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FaqDialog; }
QT_END_NAMESPACE

class FaqDialog : public QWidget
{
    Q_OBJECT

public:
    FaqDialog(QWidget *parent = nullptr);
    ~FaqDialog();

private slots:
    void on_pbtnClose_clicked();

private:
    Ui::FaqDialog *uid;
};

#endif // UI_FAQ_DIALOG_H
