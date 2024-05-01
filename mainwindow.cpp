#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "realization//upload_user_code.cpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged()
{
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");
    ui->user_input_data->clear();
}

