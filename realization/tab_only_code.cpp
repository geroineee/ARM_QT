#include "realization/database_operations.h"
#include "realization/utils.h"


// запускает компиляцию и выводит на пользовательские окна
void MainWindow::for_button_compile(bool isWorkWithFile)
{
    if (!ui->user_code_text_edit->toPlainText().size())
    {
        QMessageBox::warning(this, "Ошибка", "Нельзя скомпилировать пустой код.");
        return;
    }
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
            ui->statusbar->showMessage("Файлы не выбраны!");
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
        writeToFile(file_cpp_path, user_code, false);
    }

    QString user_input_data = ui->user_input_data->toPlainText(); // входные данные из поля ввода

    file_bat_path = current_path + "start_compile.bat"; // путь до файла start_compile.bat
    file_input_path = current_path + "user_input.txt"; // путь до файла user_input.txt

    // очистка статус-бара | вывода пользователю
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");

    // запись в user_input.txt из пользовательского окна ввода
    writeToFile(file_input_path, user_input_data);

    QProcess process;
    compile_code(current_path, names);

    // запуск start_compile.bat
    process.start(current_path + "start_compile.bat");

    // проверка на ошибки и вывод
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();

    if (errors.size() != 0)
    {
        ui->statusbar->showMessage("Ошибка компиляции");
        delete_file(current_path, list_del_names);
        QMessageBox::information(this, "Ошибка компиляции", errors);
        return;
    }

    if (!process.waitForFinished(15000))
    {
        WinExec("taskkill /im user_main_code.exe /f", SW_HIDE);
        ui->statusbar->showMessage("Runtime Error");
        delete_file(current_path, list_del_names);
        QMessageBox::critical(this, "Runtime Error", "Превышено время ожидания выполнения программы.");
        return;
    }

    QString output_data = QString::fromLocal8Bit(process.readAll());
    ui->to_user_output_data->setText(output_data);
    ui->statusbar->showMessage("Успешное выполнение кода!");

    delete_file(current_path, list_del_names);
}

// запускает компиляцию и выводит на пользовательские окна
void MainWindow::for_button_compile()
{
    QString file_bat_path; // путь до файла .bat
    QString current_path; // путь до рабочей папки
    QStringList names;

    names = get_name_from_path(files_path);
    QString path = files_path[0];
    int index;
    for (index = path.size()-1; index > 0 && path[index] != "/"; index--);
    current_path = path.remove(index+1, path.size()-index);

    file_bat_path = current_path + "start_compile.bat"; // путь до файла start_compile.bat

    // очистка статус-бара | вывода пользователю
    ui->statusbar->showMessage("");

    QProcess process;
    compile_code(current_path, names, true);

    // запуск start_compile.bat
    process.start(current_path + "start_compile.bat");

    // проверка на ошибки и вывод
    process.waitForReadyRead();

    QByteArray errors = process.readAllStandardError();

    if (errors.size() != 0)
    {
        qDebug() << errors;
        ui->statusbar->showMessage("Ошибка компиляции");
        QMessageBox::information(this, "Ошибка компиляции", errors);
        return;
    }

    process.waitForFinished();

}


int MainWindow::check_test(QString input_data, QString waiting_output_data)
{
    QString file_input_path; // путь до файла .txt
    QString current_path; // путь до рабочей папки
    QTextStream writeStream; // поток для записи в файл
    QStringList list_del_names = { "user_input.txt", "user_output.txt", "user_main_code.exe", "start_check_test.bat" }; // список для удаления файлов

    QString path = files_path[0];
    int index;
    for (index = path.size()-1; index > 0 && path[index] != "/"; index--);
    current_path = path.remove(index+1, path.size()-index);

    file_input_path = current_path + "user_input.txt"; // путь до файла user_input.txt

    // очистка статус-бара | вывода пользователю
    ui->statusbar->showMessage("");

    // запись в user_input.txt входных данных теста
    writeToFile(file_input_path, input_data, true);

    QProcess process;

    QFile temp_file(current_path + "start_check_test.bat");

    if (!temp_file.exists())
        bat_for_check_test(current_path);

    // запуск start_check_test.bat
    process.start(current_path + "start_check_test.bat");

    // проверка на ошибки и вывод
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();

    if (errors.size() != 0)
    {
        delete_file(current_path, list_del_names);
        return -1;
    }

    if (!process.waitForFinished(10000))
    {
        WinExec("taskkill /im user_main_code.exe /f", SW_HIDE);
        delete_file(current_path, list_del_names);
        return 0;
    }

    QString output_data = QString::fromLocal8Bit(process.readAll());
    writeToFile(current_path + "user_output.txt", output_data);

    if (output_data == waiting_output_data)
    {
        return 1;
    }
    return 2;
}

// запуск компиляции c кодом в соответствующем поле
void MainWindow::on_upload_user_code_button_clicked()
{
    for_button_compile(false);
}

// запуск компиляции c кодом из файлов
void MainWindow::on_button_compile_file_clicked()
{
    if (isCyrillic(files_path))
    {
        ui->statusbar->showMessage("Ошибка! В имени файла или в пути к директории файла присутствует кириллица");
        return;
    }
    for_button_compile(true);
}

void MainWindow::on_button_start_test_clicked()
{
    if (files_path.size() == 0)
    {
        ui->statusbar->showMessage("Файлы не выбраны!");
        return;
    }

    for_button_compile();

    QString current_path = files_path[0];
    int index;
    for (index = current_path.size()-1; index > 0 && current_path[index] != "/"; index--);
    current_path.remove(index+1, current_path.size()-index);

    QStringList list_del_names = { "user_input.txt", "user_output.txt", "user_main_code.exe", "start_check_test.bat" };

    QString test_result, input_data = "", output_data = "", expected_output = "";

    int test_index;
    bool isLatestTestAccepted = true;
    for (test_index = 0; test_index < tests.size() && isLatestTestAccepted; test_index++)
    {
        int result = check_test(tests[test_index][2].toString(), tests[test_index][3].toString());
        switch (result)
        {
        case -1:
            test_result = "Ошибка при выполнении кода";
            output_data = "Ошибка в коде";
            isLatestTestAccepted = false;
            break;
        case 0:
            test_result = "Превышено время выполнения кода";
            output_data = "Runtime Error";
            isLatestTestAccepted = false;
            break;
        case 2:
            test_result = "Неверный ответ";
            readFromFile(current_path + "user_output.txt", output_data);
            delete_file(current_path, list_del_names);
            isLatestTestAccepted = false;
            break;
        case 1:
            break;
        default:
            break;
        }
    }

    QString date = getCurrentDateTime();
    QString query;
    QSqlQuery q(database);
    QString person_id;

    if (current_name == "")
        current_name = "Неизвестный";

    if (existsRecord("Person", "person_name", current_name))
        query = updateData("Person", {"date"}, {date}, "person_name = '" + current_name + "'");
    else
        query = makeInsertQuery("Person", {"date", "person_name"}, {date, current_name}, database);


    q.prepare(query);
    q.exec();

    q.clear();

    db_model_Person->select();

    person_id = getResult(getDBDataQuery("Person", "id", "person_name", current_name)).toString();

    if (isLatestTestAccepted)
    {
        test_result = "Зачтено";
        delete_file(current_path, list_del_names);
    }
    else
    {
        input_data = tests[test_index-1][2].toString();
        expected_output = tests[test_index-1][3].toString();
    }

    query = makeInsertQuery("CheckedWorks", {"person_id", "date", "work_name", "task", "status", "input_data", "expected_output", "output_data"},
                            {person_id, date, current_lab_name, ui->text_info_task->toPlainText(), test_result, input_data, expected_output, output_data}, database);
    q.prepare(query);
    q.exec();

    int test_id = getResult(getDBDataQuery("CheckedWorks", "id", {"person_id", "date", "work_name", "task", "status", "input_data", "expected_output", "output_data"},
                                           {person_id, date, current_lab_name, ui->text_info_task->toPlainText(), test_result, input_data, expected_output, output_data})).toInt();

    db_model_current_test->setFilter(QString("id = %1").arg(test_id));
    db_model_current_test->select();
}
