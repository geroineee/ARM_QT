#include "textwindow.h"
#include "ui_usercodewindow.h"


usercodewindow::usercodewindow(QWidget *parent, QString text_code) : QDialog(parent), ui(new Ui::usercodewindow)
{
    ui->setupUi(this);
    ui->text_user_code->setText(text_code);
    this->setMinimumSize(300,300);
}

usercodewindow::~usercodewindow()
{
    delete ui;
}

void usercodewindow::resizeEvent(QResizeEvent *event)
{
    ui->text_user_code->setGeometry(0, 0, event->size().width(), event->size().height());
}
