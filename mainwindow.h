#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "textwindow.h"

#include "testwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QDebug>
#include <QResizeEvent>

#include "realization/database_operations.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    bool receiveQuery(QString query);

private slots:
    void on_upload_user_code_button_clicked();
    void on_tabWidget_currentChanged();
    void on_button_get_path_files_clicked();
    void on_list_selected_files_itemDoubleClicked(QListWidgetItem *item);
    void on_button_add_test_clicked();
    void on_button_switch_mode_clicked();
    void on_button_get_files_clicked();
    void on_list_files_itemDoubleClicked(QListWidgetItem *item);
    void on_button_compile_file_clicked();
    void on_button_delete_test_clicked();

private:
    void choose_files();
    void for_button_compile(bool isWorkWithFile);
    void showUserCode(QListWidget*, QListWidgetItem*);
    void resizeEvent(QResizeEvent *event);

    testwindow *testWindow;
    usercodewindow *code_window;
    Ui::MainWindow *ui;

    // пути до выбранных файлов
    QStringList files_path;

    // для работы с базой данных
    QSqlDatabase database;
    QSqlTableModel *db_model;

};
#endif // MAINWINDOW_H
