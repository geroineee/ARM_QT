#include "testwindow.h"
#include "ui_testwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "realization/utils.h"
#include "realization/database_operations.h"

testwindow::testwindow(QSqlDatabase& database, QWidget *parent)
    : QDialog(parent), ui(new Ui::testwindow), m_database(database)
{
    ui->setupUi(this);

    db_model_tests = new QSqlTableModel(this, m_database);
    db_model_tests->setTable("Tests");

    ui->list_of_tests->resizeColumnsToContents();

    db_model_tests->setHeaderData(2, Qt::Horizontal, tr("Входные"));
    db_model_tests->setHeaderData(3, Qt::Horizontal, tr("Выходные"));
    ui->list_of_tests->setModel(db_model_tests);

    ui->list_of_tests->setColumnHidden(0, true);
    ui->list_of_tests->setColumnHidden(1, true);

    db_model = new QSqlTableModel(this, m_database);
    db_model->setTable("Variants");

    ui->list_variants->resizeColumnsToContents();

    db_model->setHeaderData(3, Qt::Horizontal, tr("Номер варианта"));
    ui->list_variants->setModel(db_model);

    ui->list_variants->setColumnHidden(0, true);
    ui->list_variants->setColumnHidden(1, true);
    ui->list_variants->setColumnHidden(2, true);
}

testwindow::~testwindow()
{
    delete ui;
}

void testwindow::closeEvent(QCloseEvent *evnt)
{
    if (evnt->spontaneous())
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
}


void testwindow::on_button_add_variant_clicked()
{
    if (ui->lineEdit_lab_name->text() != "" && ui->TextEdit_lab_desc->toPlainText() != "")
    {
        QString query;
        ui->stackedWidget->setCurrentIndex(1);

        ui->label_number_variant->setText(QString::number(current_var_number));

        ui->TextEdit_variant->clear();

        QStringList tables = {"name", "description"};
        QStringList data;
        data << ui->lineEdit_lab_name->text() << ui->TextEdit_lab_desc->toPlainText();

        if (current_lab_id)
        {
            QString query_name = getResult(getDBDataQuery("LabWork", "name", "id", QString::number(current_lab_id))).toString();
            QString query_desc = getResult(getDBDataQuery("LabWork", "description", "id", QString::number(current_lab_id))).toString();
            if (query_name != data[0] || query_desc != data[1])
            {
                query = updateData("LabWork", tables, data, "id = " + QString::number(current_lab_id));
                emit sendQuery(query);
            }
        }
        else
        {
            query = makeInsertQuery("LabWork", tables, data, this->m_database);
            emit sendQuery(query);

            query = getDBDataQuery("LabWork", "id", "name", data[0]);
            current_lab_id = getResult(query).toInt();
        }
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}

void testwindow::on_button_add_tests_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QString variant = ui->TextEdit_variant->toPlainText();
    if (variant.size())
    {
        QStringList tables = {"labwork_id", "conditions" , "number_var"};
        QStringList data;
        data << QString::number(current_lab_id) << variant << QString::number(current_var_number);
        QString query;

        if (current_var_id)
        {
            query = updateData("Variants", tables, data, "id = " + QString::number(current_var_id));
            emit sendQuery(query);
        }
        else
        {
            query = makeInsertQuery("Variants", tables, data, this->m_database);
            emit sendQuery(query);

            query = getDBDataQuery("Variants", "id", "conditions", data[1]);
            current_var_id = getResult(query).toInt();
        }
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}

// вывод текста выбранного файла в новом окне
// item_index - индекс элемента списка (и пути этого элемента в files_path), на который нажал пользователь
void testwindow::showUserCode(QListWidget* widget, QListWidgetItem *item)
{
    QString text_code;
    int item_index = widget->currentRow();
    readFromFile(files_path[item_index], text_code);
    code_window = new usercodewindow(this, text_code);
    code_window->setWindowTitle(item->text());
    code_window->show();
    code_window->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}


void testwindow::choose_files()
{
    QStringList temp_paths; // нужен, если пользователь случайно нажал (не хотел выбирать файлы), чтобы список не очищался
    QString current_path; // для запоминания последней директории

    if (files_path.isEmpty())
        current_path = QDir::currentPath();

    // выбор файла
    temp_paths = QFileDialog::getOpenFileNames(this, "Выберите файл", current_path, "Cpp and Header Files (*.*)");

    // проверка на пустую директорию
    if (temp_paths.isEmpty())
    {
        return;
    }
    files_path = temp_paths;

    current_path = files_path[0];

    // очистка listWidget
    ui->list_files->clear();

    // заполнение списка
    fillSelecteFilesTable(files_path, ui->list_files);
}

// запускает компиляцию и выводит на пользовательские окна
void testwindow::button_compile(bool isWorkWithFile)
{
    QString file_bat_path; // путь до файла .bat
    QString file_cpp_path; // путь до файла .cpp
    QString file_input_path; // путь до файла .txt
    QString current_path; // путь до рабочей папки
    QTextStream writeStream; // поток для записи в файл
    QStringList names;
    QStringList list_del_names = { "user_input.txt", "user_output.txt" }; // список для удаления файлов

    if (isWorkWithFile)
    {
        if (files_path.size() == 0)
        {
            QMessageBox::warning(this, "Ошибка", "Файлы не выбраны!");
            return;
        }
        names = get_name_from_path(files_path);
        QString path = files_path[0];
        int index;
        for (index = path.size()-1; index > 0 && path[index] != "/"; index--);
        current_path = path.remove(index+1, path.size()-index);
    }
    else
    {
        names.append("user_main_code.cpp");
        list_del_names.append("user_main_code.cpp");
        current_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3);
        file_cpp_path = current_path + "user_main_code.cpp"; // путь до файла user_main_code.cpp

        QString user_code = ui->user_code_text_edit->toPlainText(); // код из тектового поля ввода

        // открытие user_main_code.cpp и запись в него код из пользовательского окна
        writeToFile(file_cpp_path, user_code);
    }

    QString user_input_data = ui->user_input_data->toPlainText(); // входные данные из поля ввода

    file_bat_path = current_path + "start_compile.bat"; // путь до файла start_compile.bat
    file_input_path = current_path + "user_input.txt"; // путь до файла user_input.txt

    // очистка вывода пользователю
    ui->to_user_output_data->setPlainText("");

    // запись в user_input.txt из пользовательского окна ввода
    writeToFile(file_input_path, user_input_data);

    QProcess process;
    compile_code(process, current_path, names);

    // проверка на ошибки и вывод
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();

    if (errors.size() != 0)
    {
        delete_file(current_path, list_del_names);
        QMessageBox::information(this, "Ошибка компиляции", errors);
        return;
    }

    if (!process.waitForFinished(15000))
    {
        WinExec("taskkill /im user_main_code.exe /f", SW_HIDE);
        delete_file(current_path, list_del_names);
        QMessageBox::critical(this, "Runtime Error", "Превышено время ожидания выполнения программы.");
        return;
    }

    QString output_data = QString::fromLocal8Bit(process.readAll());
    ui->to_user_output_data->setPlainText(output_data);

    delete_file(current_path, list_del_names);
}


void testwindow::on_upload_user_code_button_clicked()
{
    button_compile(false);
}


void testwindow::on_button_switch_mode_clicked()
{
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");

    // очистка виджетов ввода/вывода программы
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
    }
}


void testwindow::on_button_compile_file_clicked()
{
    button_compile(true);
}


void testwindow::on_button_get_files_clicked()
{
    choose_files();
}


void testwindow::on_list_files_itemDoubleClicked(QListWidgetItem *item)
{
    showUserCode(ui->list_files, item);
}


void testwindow::on_button_test_append_clicked()
{
    QString input_data, output_data;
    input_data = ui->user_input_data->toPlainText();
    output_data = ui->to_user_output_data->toPlainText();

    if (input_data.size() || output_data.size())
    {
        QStringList tables = {"variant_id", "input_data", "output_data"};
        QStringList data;
        data << QString::number(current_var_id) << input_data << output_data;
        QString query = makeInsertQuery("Tests", tables, data, this->m_database);
        emit sendQuery(query);

        QMessageBox messageBox(QMessageBox::Question,
                               tr("Успешно!"),
                               tr("Тест успешно добавлен,\nхотите добавить еще?"),
                               QMessageBox::Yes | QMessageBox::No,
                               this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
        messageBox.setButtonText(QMessageBox::No, tr("Нет"));

        if (messageBox.exec() == QMessageBox::No)
        {
            ui->stackedWidget->setCurrentIndex(1);
            db_model_tests->setFilter(QString("variant_id = %1").arg(current_var_id));
            db_model_tests->select();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Хотя бы одно поле должно быть заполнено"));
    }
}


void testwindow::on_button_save_variant_clicked()
{
    QString variant_data;
    variant_data = ui->TextEdit_variant->toPlainText();

    if (variant_data.size())
    {
        QStringList tables = {"labwork_id", "conditions", "number_var"};
        QStringList data;
        data << QString::number(current_lab_id) << variant_data << QString::number(current_var_number);
        QString query;

        if (current_var_id)
        {
            query = updateData("Variants", tables, data, "id = " + QString::number(current_var_id));
            emit sendQuery(query);
        }
        else
        {
            query = makeInsertQuery("Variants", tables, data, this->m_database);
            emit sendQuery(query);

            query = getDBDataQuery("Variants", "id", "conditions", data[1]);
            QSqlQuery q(query);
            if (q.next())
            {
                current_var_id = q.value(0).toInt();
            }
        }

        db_model->setFilter(QString("labwork_id = %1").arg(current_lab_id));
        db_model->select();

        current_var_number = getNextFreeNumberVar(this->m_database, current_lab_id);
        current_var_id = 0;
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}


void testwindow::on_button_save_lab_clicked()
{
    if (ui->lineEdit_lab_name->text() != "" && ui->TextEdit_lab_desc->toPlainText() != "")
    {
        QStringList tables = {"name", "description"};
        QStringList data;
        QString query = "";
        data << ui->lineEdit_lab_name->text() << ui->TextEdit_lab_desc->toPlainText();

        if (current_lab_id)
        {
            QString query_name = getResult(getDBDataQuery("LabWork", "name", "id", QString::number(current_lab_id))).toString();
            QString query_desc = getResult(getDBDataQuery("LabWork", "description", "id", QString::number(current_lab_id))).toString();
            if (query_name != data[0] || query_desc != data[1])
            {
                query = updateData("LabWork", tables, data, "id = " + QString::number(current_lab_id));
            }
        }
        else
        {
            query = makeInsertQuery("LabWork", tables, data, this->m_database);
        }

        if (query.size())
            emit sendQuery(query);

        current_lab_id = 0;
        current_var_number = 1;
        close();
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}

void testwindow::on_button_delete_variant_clicked()
{
    int current_row = ui->list_variants->currentIndex().row();
    int variant_id = db_model->index(current_row, 0).data().toInt();

    // Удаление зависимостей из таблицы Tests
    QSqlQuery query;
    query.prepare("DELETE FROM Tests WHERE variant_id = :variant_id");
    query.bindValue(":variant_id", variant_id);
    query.exec();

    // Удаление записи из таблицы LabWork
    db_model->removeRow(current_row);
    db_model->select();
}


void testwindow::on_button_delete_tests_clicked()
{
    int current_row = ui->list_of_tests->currentIndex().row();
    db_model_tests->removeRow(current_row);
    db_model_tests->select();
}

