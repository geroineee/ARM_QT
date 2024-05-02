#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "realization/workWithFiles.cpp"

#include <Windows.h>

#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>

QFile* tryToOpen(QString file_path)
{
    QFile *file = new QFile;
    file->setFileName(file_path);
    if (!file->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
        return nullptr;
    }
    return file;
}

// запись в файл, находящегося по пути path_to_file, данных data_to_write
void writeToFile(QString path_to_file, QString data_to_write)
{
    QTextStream writeStream;
    QFile *file;
    file = tryToOpen(path_to_file);
    if (file == nullptr)
        return;
    writeStream.setDevice(file);
    writeStream << data_to_write;
    file->close();
}

// удаление всех файлов с именами file_names, которые лежат по пути current_path
void delete_file(QString current_path, QStringList file_names)
{
    QString del_command = "@echo off\n"
                          "cd /D " + current_path + "\n";
    for (const QString& file_name : qAsConst(file_names))
    {
        del_command.append("del " + file_name + "\n");
    }
    del_command.append("del delete_bat.bat\nexit");

    writeToFile(current_path + "delete_bat.bat", del_command);
    QProcess process_del;
    process_del.start(current_path + "delete_bat.bat");
    process_del.waitForFinished();
}

// Компилирует код и возвращает указатель на QProcess | directory_path передается без "/" |
void compile_code(QProcess& process, QString directory_path, QStringList file_names)
{
    QString compiled_files = "";
    for (const QString& file : qAsConst(file_names))
    {
        compiled_files.append(file + " ");
    }
    // открытие и запись в start_compile.bat
    QString command = "@echo off\n"
                      "chcp 65001 > null.txt\n"
                      "cd /D " + directory_path + "\n"
                      "g++ " + compiled_files + "-o user_main_code.exe\n"
                      "user_main_code.exe < user_input.txt\n"
                      "del user_main_code.exe\n"
                      "del null.txt\n"
                      "del start_compile.bat\n"
                      "exit";
    writeToFile(directory_path + "start_compile.bat", command);

    // запуск start_compile.bat
    process.start(directory_path + "start_compile.bat");
}

void MainWindow::on_upload_user_code_button_clicked()
{
    QString file_bat_path; // путь до файла .bat
    QString file_cpp_path; // путь до файла .cpp
    QString file_input_path; // путь до файла .txt
    QString file_output_path; // путь до файла .txt
    QString current_path; // путь до рабочей папки
    QTextStream writeStream; // поток для записи в файл

    QString user_code = ui->user_code_text_edit->toPlainText(); // код из тектового поля ввода
    QString user_input_data = ui->user_input_data->toPlainText(); // входыне данные из поля ввода

    current_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3);
    file_bat_path = current_path + "start_compile.bat"; // путь до файла start_compile.bat
    file_cpp_path = current_path + "user_main_code.cpp"; // путь до файла user_main_code.cpp
    file_input_path = current_path + "user_input.txt"; // путь до файла user_input.txt
    file_output_path = current_path + "user_output.txt"; // путь до файла user_output.txt
    QStringList list_del_names = { "user_main_code.cpp", "user_input.txt", "user_output.txt" }; // список для удаления файлов

    // очистка статус-бара | вывода пользователю
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");

    // запись в user_input.txt из пользовательского окна ввода
    writeToFile(file_input_path, user_input_data);

    // открытие user_main_code.cpp и запись в него код из пользовательского окна
    writeToFile(file_cpp_path, user_code);

    QProcess process;
    compile_code(process, current_path, { "user_main_code.cpp" });

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
    else if (!process.waitForFinished(15000))
    {
        WinExec("taskkill /im user_main_code.exe /f", SW_HIDE);
        ui->statusbar->showMessage("Runtime Error");
        delete_file(current_path, list_del_names);
        QMessageBox::critical(this, "Runtime Error", "Превышено время ожидания выполнения программы.");
        return;
    }

    QString output_data = QString::fromLocal8Bit(process.readAll());
    writeToFile(file_output_path, output_data);
    ui->to_user_output_data->setText(output_data);
    ui->statusbar->showMessage("Успешное выполнение кода!");

    delete_file(current_path, list_del_names);
}
