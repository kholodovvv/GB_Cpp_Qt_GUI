#pragma once

#include <QWidget>

#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ChangeThemeWindow: public QWidget
{
    Q_OBJECT

public:
    ChangeThemeWindow(QWidget* parent = nullptr);
    qint8 getThemeIdx();

public slots:
    void on_ChangeTheme();

signals:
    void change_theme();

private:
    QGroupBox* pGrpBox;
    QComboBox* pCmbBox;
    QPushButton* btnEditTheme;
    QVBoxLayout* hLayout;
    QLabel* lblText;
};
