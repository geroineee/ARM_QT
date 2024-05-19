#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "textwindow.h"
#include "testwindow.h"
#include "choosework.h"
#include "moredetails.h"

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

    void on_button_edit_test_clicked();

    void on_button_get_task_clicked();

    void write_task(int id_lab, int id_var, QString name);

    void on_combo_box_example_currentIndexChanged(int index);

    void on_button_start_test_clicked();

    void on_lineEdit_name_for_search_textChanged(const QString &arg1);

    void on_list_of_all_solves_doubleClicked(const QModelIndex &index);

    void on_button_back_to_names_clicked();

    void on_checkBox_only_good_task_stateChanged(int arg1);

    void on_user_code_text_edit_textChanged();

    void on_table_result_test_doubleClicked(const QModelIndex &index);

private:
    void choose_files();
    void for_button_compile(bool isWorkWithFile);
    void for_button_compile();
    void showUserCode(QListWidget*, QListWidgetItem*);
    void resizeEvent(QResizeEvent *event);
    int check_test(QString input_data, QString waiting_output_data);

    testwindow *testWindow;
    usercodewindow *code_window;
    choosework *choose_window;
    moredetails *moredetails_window;
    Ui::MainWindow *ui;

    // пути до выбранных файлов
    QStringList files_path;

    // имя в текущей проверке
    QString current_name;
    QString current_lab_name;
    QString current_person_id;

    // список всех тестов для текущей работы
    QVector<QVariantList> tests;

    // для работы с базой данных
    QSqlDatabase database;
    QSqlTableModel *db_model;
    QSqlTableModel *db_model_Person;
    QSqlTableModel *db_model_all_test_of_Person;
    QSqlTableModel *db_model_current_test;

};
#endif // MAINWINDOW_H
