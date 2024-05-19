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
        db_model_Person = new QSqlTableModel(this, database);
        db_model_current_test = new QSqlTableModel(this, database);
        db_model_all_test_of_Person = new QSqlTableModel(this, database);

        db_model->setTable("LabWork");
        db_model_Person->setTable("Person");
        db_model_current_test->setTable("CheckedWorks");
        db_model_all_test_of_Person->setTable("CheckedWorks");

        ui->list_tests->resizeColumnsToContents();
        ui->list_of_all_solves->resizeColumnsToContents();
        ui->table_result_test->resizeColumnsToContents();

        db_model->select();
        db_model_Person->setSort(1, Qt::DescendingOrder); // сортировка по дате
        db_model_Person->select();

        db_model->setHeaderData(1, Qt::Horizontal, tr("Название работы"));

        db_model_Person->setHeaderData(1, Qt::Horizontal, tr("Дата последней проверки"));
        db_model_Person->setHeaderData(2, Qt::Horizontal, tr("Имя"));

        db_model_current_test->setHeaderData(5, Qt::Horizontal, tr("Статус проверки"));

        db_model_all_test_of_Person->setHeaderData(2, Qt::Horizontal, tr("Дата проверки"));
        db_model_all_test_of_Person->setHeaderData(3, Qt::Horizontal, tr("Название работы"));
        db_model_all_test_of_Person->setHeaderData(5, Qt::Horizontal, tr("Статус проверки"));

        ui->list_tests->setModel(db_model);
        ui->list_tests->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->list_of_all_solves->setModel(db_model_Person);
        ui->list_of_all_solves->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->table_result_test->setModel(db_model_current_test);
        ui->table_result_test->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->list_tests->setColumnHidden(0, true);
        ui->list_tests->setColumnHidden(2, true);
        ui->list_of_all_solves->setColumnHidden(0, true);
        ui->table_result_test->setColumnHidden(0, true);
        ui->table_result_test->setColumnHidden(1, true);
        ui->table_result_test->setColumnHidden(2, true);
        ui->table_result_test->setColumnHidden(3, true);
        ui->table_result_test->setColumnHidden(4, true);
        ui->table_result_test->setColumnHidden(6, true);
        ui->table_result_test->setColumnHidden(7, true);
        ui->table_result_test->setColumnHidden(8, true);
    }
    ui->text_input_example->setPlainText("Выберите работу");
    ui->text_output_example->setPlainText("Выберите работу");

    ui->lineEdit_name_for_search->setPlaceholderText("Введите имя для поиска");
    QPalette pal = ui->lineEdit_name_for_search->palette();
    pal.setColor(QPalette::Text, QColor(140, 140, 140));
    ui->lineEdit_name_for_search->setPalette(pal);

    ui->checkBox_only_good_task->hide();
    ui->button_back_to_names->hide();
    ui->label_name->hide();
    ui->label_name_change->hide();
}


MainWindow::~MainWindow()
{
    delete ui;
}

// очистка интерфейса при смене вкладки
void MainWindow::on_tabWidget_currentChanged()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        db_model_current_test->setFilter("id = -1");
        db_model_current_test->select();
        ui->combo_box_example->setCurrentIndex(0);
        ui->text_info_task->clear();
        tests.clear();
        if (ui->tabWidget->currentIndex() == 0)
            ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        ui->list_tests->setColumnWidth(1, ui->list_tests->width() + 138);

    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->to_user_output_data->setText("");
        ui->user_input_data->clear();
        if (ui->stacked_widget_modes->currentIndex())
            ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");

    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
        on_button_back_to_names_clicked();
    }

    ui->statusbar->showMessage("");
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
    ui->to_user_output_data->clear();
    ui->user_input_data->clear();

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
        QMessageBox messageBox(QMessageBox::Question,
                                       tr("Вы уверены?"),
                                       tr("Вы уверены, что хотите удалить\nнавсегда и безвозвратно?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       this);
                messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
                messageBox.setButtonText(QMessageBox::No, tr("Нет"));

        if (messageBox.exec() == QMessageBox::Yes)
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

    if (ui->button_back_to_names->isHidden())
    {
        ui->list_of_all_solves->setColumnWidth(1, (this->width()-48) * 0.3);
        ui->list_of_all_solves->setColumnWidth(2, (this->width()-48) * 0.7 - 25);
    }
    else
    {
        ui->list_of_all_solves->setColumnWidth(2, (this->width()-48) * 0.3);
        ui->list_of_all_solves->setColumnWidth(3, (this->width()-48) * 0.5 - 25);
        ui->list_of_all_solves->setColumnWidth(5, (this->width()-48) * 0.2);
    }

    ui->table_result_test->setColumnWidth(5, ui->table_result_test->width() + 134);
    event->accept();
}


void MainWindow::on_button_edit_test_clicked()
{
    int current_row = ui->list_tests->currentIndex().row();
    QModelIndex columnIndex = ui->list_tests->model()->index(current_row, 0);
    int current_lab_id = ui->list_tests->model()->data(columnIndex).toInt();
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
    db_model_current_test->setFilter("id = -1");
    db_model_current_test->select();
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


void MainWindow::write_task(int id_lab, int id_var, QString name)
{
    current_name = name;
    current_lab_name = getResult(getDBDataQuery("LabWork", "name", "id", QString::number(id_lab))).toString();

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

void MainWindow::on_lineEdit_name_for_search_textChanged(const QString &arg1)
{
    QPalette pal = ui->lineEdit_name_for_search->palette();
    if (arg1 != "")
    {
        pal.setColor(QPalette::Text, QColor(0, 0, 0));
        ui->lineEdit_name_for_search->setPalette(pal);
        db_model_Person->setFilter(QString("person_name LIKE  '%%1%'").arg(arg1));
        db_model_Person->setSort(1, Qt::DescendingOrder); // сортировка по дате
        db_model_Person->select();
    }
    else
    {
        pal.setColor(QPalette::Text, QColor(140, 140, 140));
        ui->lineEdit_name_for_search->setPalette(pal);
        db_model_Person->setFilter("");
        db_model_Person->setSort(1, Qt::DescendingOrder); // сортировка по дате
        db_model_Person->select();
    }
}


void MainWindow::on_list_of_all_solves_doubleClicked(const QModelIndex &index)
{
    QModelIndex columnIndex = ui->list_of_all_solves->model()->index(index.row(), 0);
    QVariant data = ui->list_of_all_solves->model()->data(columnIndex);

    if (data.isValid())
    {
        if (!ui->lineEdit_name_for_search->isHidden())
        {
            ui->lineEdit_name_for_search->hide();
            ui->button_back_to_names->show();
            ui->checkBox_only_good_task->show();
            ui->label_name->show();
            ui->label_name_change->show();

            current_person_id = data.toString();

            QString person_name = getResult(getDBDataQuery("Person", "person_name", "id", current_person_id)).toString();
            ui->label_name_change->setText(person_name);

            ui->list_of_all_solves->setModel(db_model_all_test_of_Person);
            ui->list_of_all_solves->setEditTriggers(QAbstractItemView::NoEditTriggers);

            ui->list_of_all_solves->setColumnHidden(0, true);
            ui->list_of_all_solves->setColumnHidden(1, true);
            ui->list_of_all_solves->setColumnHidden(4, true);
            ui->list_of_all_solves->setColumnHidden(6, true);
            ui->list_of_all_solves->setColumnHidden(7, true);
            ui->list_of_all_solves->setColumnHidden(8, true);

            ui->list_of_all_solves->setColumnWidth(2, (this->width()-48) * 0.3);
            ui->list_of_all_solves->setColumnWidth(3, (this->width()-48) * 0.5 - 25);
            ui->list_of_all_solves->setColumnWidth(5, (this->width()-48) * 0.2);

            db_model_all_test_of_Person->setFilter(QString("person_id = %1").arg(current_person_id));
            db_model_all_test_of_Person->setSort(2, Qt::DescendingOrder); // сортировка по дате
            db_model_all_test_of_Person->select();
        }
        else
        {
            moredetails_window = new moredetails(database, this, data.toInt());
            moredetails_window->setWindowTitle("Подробнее об отчете");
            moredetails_window->setModal(true);
            moredetails_window->exec();
        }
    }
}


void MainWindow::on_button_back_to_names_clicked()
{
    ui->lineEdit_name_for_search->clear();
    ui->label_name_change->clear();

    ui->list_of_all_solves->setModel(db_model_Person);
    ui->list_of_all_solves->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->list_of_all_solves->showColumn(1);

    ui->list_of_all_solves->setColumnWidth(1, (this->width()-48) * 0.3);
    ui->list_of_all_solves->setColumnWidth(2, (this->width()-48) * 0.7 - 25);

    db_model_Person->setFilter("");
    db_model_Person->setSort(1, Qt::DescendingOrder); // сортировка по дате
    db_model_Person->select();

    ui->checkBox_only_good_task->setCheckState(Qt::Unchecked);

    ui->button_back_to_names->hide();
    ui->checkBox_only_good_task->hide();
    ui->label_name->hide();
    ui->label_name_change->hide();
    ui->lineEdit_name_for_search->show();
}


void MainWindow::on_checkBox_only_good_task_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        db_model_all_test_of_Person->setFilter(QString("person_id = '%1' AND status = '%2'").arg(current_person_id, QString("Зачтено")));
        db_model_all_test_of_Person->setSort(2, Qt::DescendingOrder); // сортировка по дате

        db_model_all_test_of_Person->select();
    }
    else
    {
        db_model_all_test_of_Person->setFilter(QString("person_id = %1").arg(current_person_id));
        db_model_all_test_of_Person->setSort(2, Qt::DescendingOrder); // сортировка по дате

        db_model_all_test_of_Person->select();
    }

}

void MainWindow::on_user_code_text_edit_textChanged()
{
    QString text = ui->user_code_text_edit->toPlainText();
    QTextCursor cursor = ui->user_code_text_edit->textCursor();
    int cursorPosition = cursor.position();

    // если введен tab
    if (cursorPosition > 0 && text.at(cursorPosition - 1) == '\t')
    {
        // удалить Tab
        cursor.deletePreviousChar();
        // вставить четыре пробела
        cursor.insertText("    ");
        // обновить курсор
        ui->user_code_text_edit->setTextCursor(cursor);
    }
}


void MainWindow::on_table_result_test_doubleClicked(const QModelIndex &index)
{
    QModelIndex columnIndex = ui->table_result_test->model()->index(index.row(), 0);
    QVariant data = ui->table_result_test->model()->data(columnIndex);

    if (data.isValid())
    {
        moredetails_window = new moredetails(database, this, data.toInt());
        moredetails_window->setWindowTitle("Подробнее об отчете");
        moredetails_window->setModal(true);
        moredetails_window->exec();
    }
}

