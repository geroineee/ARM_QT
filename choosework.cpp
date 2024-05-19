#include "choosework.h"
#include "ui_choosework.h"

#include "realization/database_operations.h"
#include "realization/utils.h"

choosework::choosework(QSqlDatabase& database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choosework), m_database(database)
{
    ui->setupUi(this);

    db_model_var = new QSqlTableModel(this, m_database);
    db_model_var->setTable("Variants");

    ui->list_of_variants->resizeColumnsToContents();

    db_model_var->setHeaderData(3, Qt::Horizontal, tr("Номер варианта"));
    ui->list_of_variants->setModel(db_model_var);

    ui->list_of_variants->setColumnHidden(0, true);
    ui->list_of_variants->setColumnHidden(1, true);
    ui->list_of_variants->setColumnHidden(2, true);

    ui->list_of_variants->setColumnWidth(3, this->width()-31);

    labs = getAllInTableWhere(database, "LabWork", "id", QString::number(0), true);
    for (int i = 0; i < labs.size(); i++)
    {
        ui->comboBox_of_works->addItem(labs[i][1].toString());
    }
}

choosework::~choosework()
{
    delete ui;
}

void choosework::on_comboBox_of_works_currentIndexChanged(int index)
{
    if (index != 0)
    {
        int current_lab_id = labs[index-1][0].toInt();

        db_model_var->setFilter(QString("labwork_id = %1").arg(current_lab_id));
        db_model_var->setSort(3, Qt::SortOrder::AscendingOrder);
        db_model_var->select();
    }
    else
    {
        db_model_var->setFilter(QString("labwork_id = %1").arg(-1));
        db_model_var->select();
    }
}


void choosework::closeEvent(QCloseEvent *evnt)
{
    if (ui->comboBox_of_works->currentIndex() != 0 || ui->lineEdit_name->text() != "")
    {
        QMessageBox messageBox(QMessageBox::Question,
                               tr("Вы уверены?"),
                               tr("Несохраненные изменения будут утеряны."),
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
}


void choosework::on_button_cancel_work_clicked()
{
    close();
}


void choosework::on_button_accept_work_clicked()
{
    int current_index_lab = ui->comboBox_of_works->currentIndex();
    int current_index_var = ui->list_of_variants->currentIndex().row();
    if (current_index_lab != -1 && current_index_var != -1)
    {
        int id_lab, id_var;

        id_lab = labs[current_index_lab-1][0].toInt();

        QModelIndex index = ui->list_of_variants->model()->index(current_index_var, 0);
        id_var = index.data().toInt();

        current_name = ui->lineEdit_name->text();

        emit send_id(id_lab, id_var, current_name);

        ui->comboBox_of_works->setCurrentIndex(0);
        ui->lineEdit_name->clear();

        close();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не выбрано ни 1 работы.");
        return;
    }
}

void choosework::resizeEvent(QResizeEvent *event)
{
    ui->list_of_variants->setColumnWidth(3, this->width()-31);
    event->accept();
}
