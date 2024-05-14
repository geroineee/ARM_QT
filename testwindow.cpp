#include "testwindow.h"
#include "ui_testwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "realization/utils.h"
#include "realization/database_operations.h"

testwindow::testwindow(QWidget *parent) : QDialog(parent), ui(new Ui::testwindow)
{
    ui->setupUi(this);
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
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}

void testwindow::on_button_add_tests_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
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
        /*
     * добавить в бд тесты
        */

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
        // Добавить варик в бд

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
        data.append(ui->lineEdit_lab_name->text());
        data.append(ui->TextEdit_lab_desc->toPlainText());
        QString query = makeInsertQuery("LabWork", tables, data);
        emit sendQuery(query);
        close();
    }
    else
    {
        QMessageBox::warning(this, "Куда торопимся?", "Не все поля заполнены.");
    }
}
