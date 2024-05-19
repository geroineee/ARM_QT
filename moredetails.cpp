#include "moredetails.h"
#include "ui_moredetails.h"

#include "realization/database_operations.h"
#include "realization/utils.h"

moredetails::moredetails(QSqlDatabase& database, QWidget *parent, int test_id) :
    QDialog(parent),
    ui(new Ui::moredetails), m_database(database)
{
    ui->setupUi(this);

    ui->textBrowser_task->setPlainText(getResult(getDBDataQuery("CheckedWorks", "task", "id", QString::number(test_id))).toString());
    ui->label_status->setText(getResult(getDBDataQuery("CheckedWorks", "status", "id", QString::number(test_id))).toString());

    QString input_text, output_text, expected_text;
    input_text = getResult(getDBDataQuery("CheckedWorks", "input_data", "id", QString::number(test_id))).toString();
    expected_text = getResult(getDBDataQuery("CheckedWorks", "expected_output", "id", QString::number(test_id))).toString();
    output_text = getResult(getDBDataQuery("CheckedWorks", "output_data", "id", QString::number(test_id))).toString();

    if (input_text.size() && expected_text.size() && output_text.size())
    {
        ui->textBrowser_input_data->setText("Входные данные:\n" + input_text);
        ui->textBrowser_expected_output->setText("Ожидаемые выходные данные:\n" + expected_text);
        ui->textBrowser_output_data->setText("Выходные данные:\n" + output_text);
    }
    else
    {
        QString text = "Все тесты пройдены!";
        ui->textBrowser_input_data->setText(text);
        ui->textBrowser_expected_output->setText(text);
        ui->textBrowser_output_data->setText(text);
    }
}

moredetails::~moredetails()
{
    delete ui;
}

void moredetails::on_button_ok_clicked()
{
    close();
}

