#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include "usercodewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_upload_user_code_button_clicked();
    void on_tabWidget_currentChanged();
    void on_button_get_path_files_clicked();
    void on_list_selected_files_itemDoubleClicked(QListWidgetItem *item);

private:
    QStringList files_path;
    Ui::MainWindow *ui;
    usercodewindow *code_window;
};
#endif // MAINWINDOW_H
