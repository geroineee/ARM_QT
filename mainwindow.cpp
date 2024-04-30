#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
//#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QProcess>

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
    QString user_code = ui->user_code_text_edit->toPlainText();
    QString file_path = QDir::currentPath();
    file_path.remove(file_path.size()-3, 3).append("workspace/main_code.cpp");
    QFile output_file(file_path);
    if(!output_file.exists())
    {
        qDebug() << "Файл не существует";
    }
    else if (!output_file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
    }
    QTextStream writeStream(&output_file);
    writeStream << user_code;
    output_file.close();
}

