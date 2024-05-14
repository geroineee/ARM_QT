#include "realization/database_operations.h"
#include "realization/utils.h"


// запускает компиляцию и выводит на пользовательские окна
void MainWindow::for_button_compile(bool isWorkWithFile)
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
        writeToFile(file_cpp_path, user_code);
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
    compile_code(process, current_path, names);

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
