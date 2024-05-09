#include "testwindow.h"
#include "ui_testwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "realization/database_operations.h"

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
    {
        evnt->accept(); // Закрыть окно
    }
    else
    {
        evnt->ignore(); // Отменить закрытие окна
    }
}

void testwindow::on_button_add_variant_clicked()
{
    if (ui->lineEdit_lab_name->text() != "" && ui->TextEdit_lab_desc->toPlainText() != "")
    {
        QMessageBox messageBox(QMessageBox::Question,
                               tr("Продолжить?"),
                               tr("Изменить формулировку можно будет только в режиме редактирования."),
                               QMessageBox::Yes | QMessageBox::No,
                               this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
        messageBox.setButtonText(QMessageBox::No, tr("Нет"));

        if (messageBox.exec() == QMessageBox::No)
        {
            return;
        }

        QStringList tables = {"name", "description"};
        QStringList data;
        data.append(ui->lineEdit_lab_name->text());
        data.append(ui->TextEdit_lab_desc->toPlainText());
        QString query = makeInsertQuery("LabWork", tables, data);
        emit sendQuery(query);
        ui->stackedWidget->setCurrentIndex(1);
    }

    else
    {
        QMessageBox::warning(this, "Недостаточно данных", "Не все поля заполнены.");
    }
}


void testwindow::on_button_back_to_edie_test_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void testwindow::setRedactorMode(bool isRedactor)
{
    this->isRedactor = isRedactor;
}
