#include "realization/database_operations.h"
#include "realization/utils.h"


void MainWindow::choose_files()
{
    QStringList temp_paths; // нужен, если пользователь случайно нажал (не хотел выбирать файлы), чтобы список не очищался
    QString current_path; // для запоминания последней директории

    if (files_path.isEmpty())
        current_path = QDir::currentPath();

    // выбор файла
    temp_paths = QFileDialog::getOpenFileNames(this, "Выберите файл", current_path, "Cpp and Header Files (*.*)");

    // проверка на пустую директорию
    if (temp_paths.isEmpty())
    {
        return;
    }
    files_path = temp_paths;

    current_path = files_path[0];

    // очистка listWidget
    ui->list_selected_files->clear();
    ui->list_files->clear();

    // заполнение списка
    fillSelecteFilesTable(files_path, ui->list_files);
    fillSelecteFilesTable(files_path, ui->list_selected_files);
}

// вывод текста выбранного файла в новом окне
// item_index - индекс элемента списка (и пути этого элемента в files_path), на который нажал пользователь
void MainWindow::showUserCode(QListWidget* widget, QListWidgetItem *item)
{
    QString text_code;
    int item_index = widget->currentRow();
    readFromFile(files_path[item_index], text_code);
    code_window = new usercodewindow(this, text_code);
    code_window->setWindowTitle(item->text());
    code_window->show();
    code_window->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

// вывод текста выбранного файла в новом окне, вызванное из вкладки ""
void MainWindow::on_list_selected_files_itemDoubleClicked(QListWidgetItem *item)
{
    showUserCode(ui->list_selected_files,item);
}

// вывод текста выбранного файла в новом окне
void MainWindow::on_list_files_itemDoubleClicked(QListWidgetItem *item)
{
    showUserCode(ui->list_files,item);
}

void MainWindow::on_button_get_path_files_clicked()
{
    choose_files();
}

void MainWindow::on_button_get_files_clicked()
{
    choose_files();
}
