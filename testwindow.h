#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QListWidgetItem>

#include "textwindow.h"

namespace Ui {class testwindow;}

class testwindow : public QDialog
{
    Q_OBJECT

public:
    explicit testwindow(QWidget *parent = nullptr);
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

signals:
    void sendQuery(QString);

private:
    void button_compile(bool isWorkWithFile);
    void choose_files();
    void showUserCode(QListWidget* widget, QListWidgetItem *item);

    QStringList files_path;

    Ui::testwindow *ui;
    usercodewindow *code_window;

protected:
    void closeEvent(QCloseEvent *evnt);
};

#endif // TESTWINDOW_H
