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
    ui->text_input_example->setPlainText("Выберите работу");
    ui->text_output_example->setPlainText("Выберите работу");
}


MainWindow::~MainWindow()
{
    delete ui;
}

// очистка интерфейса при смене вкладки
void MainWindow::on_tabWidget_currentChanged()
{
    ui->combo_box_example->setCurrentIndex(0);
    ui->text_info_task->clear();
    tests.clear();

    ui->list_tests->setColumnWidth(1, ui->list_tests->width() + 138);
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");
    ui->user_input_data->clear();
    if ((ui->stacked_widget_modes->currentIndex() && ui->tabWidget->currentIndex() == 2) or ui->tabWidget->currentIndex() == 0)
        ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
}

// добавление работы по нажатию кнопки
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


void MainWindow::on_button_get_task_clicked()
{
    ui->text_input_example->setPlainText("Выберите пример");
    ui->text_output_example->setPlainText("Выберите пример");
    ui->text_info_task->clear();
    tests.clear();
    ui->combo_box_example->setCurrentIndex(0);

    choose_window = new choosework(this->database);
    choose_window->setWindowTitle("Выбор работы");
    choose_window->setModal(true);

    connect(choose_window, &choosework::send_id, this, &MainWindow::write_task);

    choose_window->exec();
}


void MainWindow::write_task(int id_lab, int id_var)
{
    QString lab_task, var_task;
    lab_task = getResult(getDBDataQuery("LabWork", "name", "id", QString::number(id_lab))).toString() + "\n";
    lab_task += getResult(getDBDataQuery("LabWork", "description", "id", QString::number(id_lab))).toString() + "\n\n\n";

    var_task = "Вариант №" + getResult(getDBDataQuery("Variants", "number_var", "id", QString::number(id_var))).toString() + "\n";
    var_task += getResult(getDBDataQuery("Variants", "conditions", "id", QString::number(id_var))).toString();

    QString task = lab_task + var_task;
    ui->text_info_task->setPlainText(task);

    tests = getAllInTableWhere(this->database, "Tests", "variant_id", QString::number(id_var));
}


void MainWindow::on_combo_box_example_currentIndexChanged(int index)
{
    QString input_text = "Входные данные:\n", output_text = "Выходные данные:\n";
    if (index == 0)
    {
        input_text = "Выберите пример";
        output_text = "Выберите пример";
    }
    else
    {
        if (index - 1 < tests.size())
        {
            input_text += tests[index-1][2].toString();
            output_text += tests[index-1][3].toString();
        }
        else
        {
            input_text = "Примера пока нет";
            output_text = "Примера пока нет";
        }
    }
    ui->text_input_example->setPlainText(input_text);
    ui->text_output_example->setPlainText(output_text);
}
