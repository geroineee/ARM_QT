#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
//#include <QDir>
#include <QFile>
#include <fstream>
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
    QString file_path = QDir::currentPath();
    QString user_code = ui->user_code_text_edit->toPlainText();

    //qDebug() << file_path;
    //std::ofstream file("C:\\Users\\sasha\\Documents\\repositories\\ARM_QT\\workspace\\main_code.cpp");
    //file.close();
}

