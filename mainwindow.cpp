#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
//#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_upload_user_code_button_clicked()
{
    QString user_code = ui->user_code_text_edit->toPlainText(); // код из тектового поля ввода

    QString file_cpp_path = QDir::currentPath(); // путь до каталога сборки "bin"
    file_cpp_path.remove(file_cpp_path.size()-3, 3).append("workspace/main_code.cpp"); // путь до файла main_code.cpp
    QFile file(file_cpp_path);
    QTextStream writeStream(&file); // поток для записи в файл

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        QMessageBox::critical(this, "Ошибка", "Ошибка при открытии\nфайла main_code.cpp");
        return;
    }

    writeStream << user_code;
    file.close();

    QString file_bat_path = QDir::currentPath().remove(QDir::currentPath().size()-3, 3) + "workspace/start_compile.bat"; // меняем файл на start_compile.bat
    file.setFileName(file_bat_path);

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        QMessageBox::critical(this, "Ошибка", "Ошибка при открытии\nфайла start_compile.bat");
        return;
    }

    writeStream << "@echo off\n"
                << "chcp 65001 > null.txt\n"
                << "cd /D " << file_cpp_path.remove(file_cpp_path.size()- 14, 14) << "\n"
                << "g++ main_code.cpp -o main_code.exe\n"
                << "main_code.exe < input.txt\n"
                << "del main_code.exe\n"
                << "del null.txt\n"
                << "exit";
    file.close();

    QProcess process;
    process.start(file_bat_path);
    process.waitForReadyRead();
    QByteArray errors = process.readAllStandardError();
    if (errors.size() == 0)
    {
        qDebug() << QString::fromLocal8Bit(process.readAll());
    }
    else
    {
        qDebug() << QMessageBox::information(this, "Ошибка компиляции", errors);
    }
    process.waitForFinished();

    ui->statusbar->showMessage("Успешное выполнение кода!");
}
