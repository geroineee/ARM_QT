#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>


QFile* tryToOpen(QString file_cpp_path)
{
    QFile *file = new QFile;
    file->setFileName(file_cpp_path);
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии\nфайла main_code.cpp");
        return nullptr;
    }
    return file;
}


void MainWindow::on_upload_user_code_button_clicked()
{
    QFile file; // обьект QFile для открытия файлов
    QString file_bat_path; // путь до файла .bat
    QString file_cpp_path; // путь до файла .cpp
    QString current_path; // путь до рабочей папки "workspace"
    QTextStream writeStream(&file); // поток для записи в файл

    QString user_code = ui->user_code_text_edit->toPlainText(); // код из тектового поля ввода

    current_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3) + "workspace/";
    file_bat_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3) + "workspace/start_compile.bat"; // путь до файла start_compile.bat
    file_cpp_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3).append("workspace/main_code.cpp"); // путь до файла main_code.cpp


    // запись в input.txt
//    file.setFileName(current_path + "input.txt");



    // открытие main_code.cpp и запись в него код из пользовательского окна
//    file = tryToOpen(file_cpp_path);

    file.setFileName(file_cpp_path);
    if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Ошибка при открытии файла";
            QMessageBox::critical(this, "Ошибка", "Ошибка при открытии\nфайла main_code.cpp");
            return;
        }

    writeStream << user_code;
    file.close();

    // открытие и запись в start_compile.bat
    file.setFileName(file_bat_path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        QMessageBox::critical(this, "Ошибка", "Ошибка при открытии\nфайла start_compile.bat");
        return;
    }

    writeStream << "@echo off\n"
                << "chcp 65001 > null.txt\n"
                << "cd /D " << current_path << "\n"
                << "g++ main_code.cpp -o main_code.exe\n"
                << "main_code.exe < input.txt\n"
                << "del main_code.exe\n"
                << "del null.txt\n"
                << "exit";
    file.close();

    // запуск start_compule.bat
    QProcess process;
    process.start(file_bat_path);

    // проверка на ошибки и вывод
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();
    if (errors.size() == 0)
    {
        qDebug() << QString::fromLocal8Bit(process.readAll());
        ui->statusbar->showMessage("Успешное выполнение кода!");
    }
    else
    {
        QMessageBox::information(this, "Ошибка компиляции", errors);
    }
    process.waitForFinished();
}
