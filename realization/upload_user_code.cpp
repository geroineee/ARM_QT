#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
        return nullptr;
    }
    return file;
}


void writeToFile(QString current_path, QString user_input_data)
{
    QTextStream writeStream;
    QFile *file;
    file = tryToOpen(current_path);
    if (file == nullptr)
        return;
    writeStream.setDevice(file);
    writeStream << user_input_data;
    file->close();
}


void MainWindow::on_upload_user_code_button_clicked()
{
    QString file_bat_path; // путь до файла .bat
    QString file_cpp_path; // путь до файла .cpp
    QString current_path; // путь до рабочей папки "workspace"
    QTextStream writeStream; // поток для записи в файл

    QString user_code = ui->user_code_text_edit->toPlainText(); // код из тектового поля ввода
    QString user_input_data = ui->user_input_data->toPlainText(); // входыне данные из поля ввода

    current_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3) + "workspace/";
    file_bat_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3) + "workspace/start_compile.bat"; // путь до файла start_compile.bat
    file_cpp_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3).append("workspace/main_code.cpp"); // путь до файла main_code.cpp

    // очистка статус-бара | вывода пользователю | файла output.txt
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");
    writeToFile(current_path + "output.txt", "");

    // запись в input.txt из пользова
    writeToFile(current_path + "input.txt", user_input_data);

    // открытие main_code.cpp и запись в него код из пользовательского окна
    writeToFile(file_cpp_path, user_code);

    // открытие и запись в start_compile.bat
    QString *temp = new QString;
    *temp = "@echo off\n"
            "chcp 65001 > null.txt\n"
            "cd /D " + current_path + "\n"
            "g++ main_code.cpp -o main_code.exe\n"
            "main_code.exe < input.txt\n"
            "del main_code.exe\n"
            "del null.txt\n"
            "exit";
    writeToFile(file_bat_path, *temp);
    delete temp;

    // запуск start_compule.bat
    QProcess process;
    process.start(file_bat_path);

    // проверка на ошибки и вывод
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();
    if (errors.size() != 0)
    {
        ui->statusbar->showMessage("Ошибка компиляции");
        QMessageBox::information(this, "Ошибка компиляции", errors);
        return;
    }

    else if (!process.waitForFinished(1000))
    {
        WinExec("taskkill /im main_code.exe /f", SW_HIDE);
        ui->statusbar->showMessage("Runtime Error");
        QMessageBox::critical(this, "Runtime Error", "Превышено время ожидания выполнения программы.");
        return;
    }

    QString output_data = QString::fromLocal8Bit(process.readAll());
    writeToFile(current_path + "output.txt", output_data);
    ui->to_user_output_data->setText(output_data);
    ui->statusbar->showMessage("Успешное выполнение кода!");

    // очистка файла main_code.cpp
    writeToFile(file_cpp_path, "");
}
