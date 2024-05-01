#include "usercodewindow.h"
#include "ui_usercodewindow.h"

usercodewindow::usercodewindow(QWidget *parent, QString text_code) : QDialog(parent), ui(new Ui::usercodewindow)
{
    ui->setupUi(this);
    ui->text_user_code->setText(text_code);
}

usercodewindow::~usercodewindow()
{
    delete ui;
}
