#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QResizeEvent>

#include "textwindow.h"

namespace Ui {class testwindow;}

class testwindow : public QDialog
{
    Q_OBJECT

public:
    explicit testwindow(QSqlDatabase& database, QWidget *parent = nullptr, int current_lab = 0);
    ~testwindow();

private slots:
    void on_button_add_variant_clicked();
    void on_button_add_tests_clicked();
    void on_upload_user_code_button_clicked();
    void on_button_switch_mode_clicked();
    void on_button_compile_file_clicked();
    void on_button_get_files_clicked();
    void on_list_files_itemDoubleClicked(QListWidgetItem *item);
    void on_button_test_append_clicked();
    void on_button_save_variant_clicked();
    void on_button_save_lab_clicked();

    void on_button_delete_variant_clicked();

    void on_button_delete_tests_clicked();

    void on_button_cancel_clicked();

    void on_button_edit_tests_clicked();

    void on_button_edit_variant_clicked();

    void on_button_cancel_variants_clicked();

    void on_button_cancel_lab_clicked();

signals:
    void sendQuery(QString);

private:
    void button_compile(bool isWorkWithFile);
    void choose_files();
    void showUserCode(QListWidget* widget, QListWidgetItem *item);
    void resizeEvent(QResizeEvent *event);

    QStringList files_path;

    int current_lab_id = 0;
    int current_var_id = 0;
    int current_var_number = 1;
    int current_test_id = 0;
    bool isEdit = false;

    Ui::testwindow *ui;
    usercodewindow *code_window;

    QSqlDatabase& m_database;
    QSqlTableModel* db_model;
    QSqlTableModel* db_model_tests;

protected:
    void closeEvent(QCloseEvent *evnt);
};

#endif // TESTWINDOW_H
