#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testwindow.h"

#include "realization//tab_only_code.cpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// очистка интерфейса при смене вкладки
void MainWindow::on_tabWidget_currentChanged()
{
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setText("");
    ui->user_input_data->clear();
}

// добавление теста по нажатию кнопки
void MainWindow::on_button_add_test_clicked()
{
    testwindow *window = new testwindow(this);
    window->setModal(true);
    window->exec();
}

void MainWindow::on_button_switch_mode_clicked()
{
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");
    if (ui->stacked_widget_modes->currentIndex())
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_code_mode);
    }
    else
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_file_mode);
    }
}
