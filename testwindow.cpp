#include "testwindow.h"
#include "ui_testwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

testwindow::testwindow(QWidget *parent) : QDialog(parent), ui(new Ui::testwindow)
{
    ui->setupUi(this);
}

testwindow::~testwindow()
{
    delete ui;
}

void testwindow::on_button_cancel_clicked()
{
    close();
}

void testwindow::closeEvent(QCloseEvent *evnt)
{
    QMessageBox messageBox(QMessageBox::Question,
                    tr("Вы уверены?"),
                    tr("Совершенные изменения не сохранятся."),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
        messageBox.setButtonText(QMessageBox::No, tr("Нет"));
        if (messageBox.exec() == QMessageBox::Yes)
            QDialog::closeEvent(evnt);
        else
            evnt->ignore();
}

void testwindow::on_button_apply_clicked()
{
    QString data = "Some data";
    emit dataEntered(data);
}
