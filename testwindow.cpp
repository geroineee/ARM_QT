#include "testwindow.h"
#include "ui_testwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "realization/workWithDB.h"

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
    if (evnt->spontaneous()) { // Если закрытие происходит через "крестик"
           QMessageBox messageBox(QMessageBox::Question,
                                  tr("Вы уверены?"),
                                  tr("Совершенные изменения не сохранятся."),
                                  QMessageBox::Yes | QMessageBox::No,
                                  this);
           messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
           messageBox.setButtonText(QMessageBox::No, tr("Нет"));

           if (messageBox.exec() == QMessageBox::Yes) {
               evnt->accept(); // Закрыть окно
           } else {
               evnt->ignore(); // Отменить закрытие окна
           }
       } else { // В противном случае, закрытие происходит по кнопке "Принять"
           evnt->accept(); // Закрыть окно без вызова messagebox
       }
}

void testwindow::on_button_apply_clicked()
{
    QStringList tables = {"name", "description"};
    QStringList data;
    data.append(ui->lineEdit_lab_name->text());
    data.append(ui->TextEdit_lab_desc->toPlainText());
    QString query = makeInsertQuery("LabWork", tables, data);
    emit sendQuery(query);
    this->close();
}
