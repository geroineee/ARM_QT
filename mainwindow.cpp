#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "realization//tab_only_code.cpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");

    database = QSqlDatabase::addDatabase("QSQLITE");
    if (tryToOpenDB(database, "Lab_works"))
    {
        db_model = new QSqlTableModel(this, database);
        db_model->setTable("LabWork");

        ui->list_tests->resizeColumnsToContents();

        db_model->select();

        db_model->setHeaderData(1, Qt::Horizontal, tr("Название работы"));

        ui->list_tests->setModel(db_model);
        ui->list_tests->setColumnHidden(0, true);
        ui->list_tests->setColumnHidden(2, true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// очистка интерфейса при смене вкладки
void MainWindow::on_tabWidget_currentChanged()
{
    ui->list_tests->setColumnWidth(1, ui->list_tests->width() + 138);
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");
    ui->user_input_data->clear();
    if ((ui->stacked_widget_modes->currentIndex() && ui->tabWidget->currentIndex() == 2) or ui->tabWidget->currentIndex() == 0)
        ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
}

// добавление теста по нажатию кнопки
void MainWindow::on_button_add_test_clicked()
{
    testWindow = new testwindow(this->database, this);
    testWindow->setWindowTitle("Добавление");

    connect(testWindow, &testwindow::sendQuery, this, &MainWindow::receiveQuery);

    testWindow->setModal(true);
    testWindow->exec();

    db_model->select();
}

void MainWindow::on_button_switch_mode_clicked()
{
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");

    // очистка статус бара \ виджетов ввода/вывода программы
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");

    if (ui->stacked_widget_modes->currentIndex())
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_code_mode);
        ui->button_switch_mode->setText("Работа с файлами");
    }
    else
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_file_mode);
        ui->button_switch_mode->setText("Работа с кодом");
        ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
    }
}

bool MainWindow::receiveQuery(QString text_query)
{
    qDebug() << "Запрос: " << text_query;
    database.exec(text_query);

    if (database.lastError().type() != QSqlError::NoError)
    {
        qDebug() << "Ошибка при выполнении запроса: " << database.lastError().text();
        return false;
    }
    return true;
}

// удаление записи из списка с тестами и базы данных
void MainWindow::on_button_delete_test_clicked()
{
    int current_row = ui->list_tests->currentIndex().row();
    int labwork_id = db_model->index(current_row, 0).data().toInt();
    if (current_row != -1)
    {
        // Удаление зависимостей из таблицы Tests
        QSqlQuery query;
        query.prepare("DELETE FROM Tests WHERE variant_id IN (SELECT id FROM Variants WHERE labwork_id = :labwork_id)");
        query.bindValue(":labwork_id", labwork_id);
        query.exec();

        // Удаление зависимостей из таблицы Variants
        query.prepare("DELETE FROM Variants WHERE labwork_id = :labwork_id");
        query.bindValue(":labwork_id", labwork_id);
        query.exec();


        // Удаление записи из таблицы LabWork
        db_model->removeRow(current_row);
        db_model->select();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не выбран ни 1 элемент.");
        return;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->list_tests->setColumnWidth(1, ui->list_tests->width() + 138);
    event->accept();
}

void MainWindow::on_button_edit_test_clicked()
{
    int current_lab_id = ui->list_tests->currentIndex().row() + 1;
    if (current_lab_id != 0)
    {
        testWindow = new testwindow(this->database, this, current_lab_id);
        testWindow->setWindowTitle("Редактирование");

        connect(testWindow, &testwindow::sendQuery, this, &MainWindow::receiveQuery);

        testWindow->setModal(true);
        testWindow->exec();

        db_model->select();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не выбран ни 1 элемент.");
        return;
    }

}

