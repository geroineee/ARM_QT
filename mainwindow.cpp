#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "testwindow.h"
//#include "ui_testwindow.h"

#include "realization//tab_only_code.cpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QSQLITE");
    if (tryToOpenDB(database, "Lab_works"))
    {
        db_model = new QSqlTableModel(this, database);
        db_model->setTable("LabWork");
        db_model->select();

        ui->list_tests->setModel(db_model);
    }
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
    if (ui->stacked_widget_modes->currentIndex() && !ui->tabWidget->currentIndex())
        ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
}

// добавление теста по нажатию кнопки
void MainWindow::on_button_add_test_clicked()
{
    testwindow *testWindow = new testwindow(this);

    connect(testWindow, &testwindow::sendQuery, this, &MainWindow::receiveQuery);

    testWindow->setModal(true);
    testWindow->exec();
}

void MainWindow::on_button_switch_mode_clicked()
{
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");

    // очистка статус бара \ виджетов ввода/вывода программы
    ui->statusbar->showMessage("");
    ui->to_user_output_data->setPlainText("");
    ui->user_input_data->setPlainText("");

    if (ui->stacked_widget_modes->currentIndex())
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_code_mode);
        ui->button_switch_mode->setText("Работа с файлами");
    }
    else
    {
        ui->stacked_widget_modes->setCurrentWidget(ui->page_file_mode);
        ui->button_switch_mode->setText("Работа с кодом");
        ui->statusbar->showMessage("Обратите внимание, что путь к файлам и их название не должны содержать кириллицу!");
    }
}

void MainWindow::receiveQuery(QString text_query)
{
    qDebug() << "Запрос: " << text_query;
    database.exec(text_query);
}
