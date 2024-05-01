#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QMessageBox>


// проверка расширения файла: 1 - .cpp \ 2 - .h \ 0 - другое
int isCppOrHeader(QString fileName)
{
    int pos = fileName.size() - 1;
    while (pos && fileName[pos] != ".")
    {
        pos--;
    }
    if (fileName.remove(0, ++pos) == "cpp")
        return 1;
    else if (fileName == "h")
        return 2;
    else
        return 0;
}


// Получение имени файла с расширением
QString getFIleName(QString path)
{
    int pos = path.size() - 1;
    while (pos && path[pos] != "/")
    {
        pos--;
    }
    return path.remove(0, ++pos);
}

void fillSelecteFilesTable(QStringList paths, Ui::MainWindow* ui)
{
    for (QString file_path : paths)
    {
        QString file_name = getFIleName(file_path);
        if (isCppOrHeader(file_name))
        {
            ui->list_selected_files->addItem(file_name);
        }
    }
}

void MainWindow::on_button_get_path_files_clicked()
{
    // получения пути до файлов
    QStringList files_path = QFileDialog::getOpenFileNames(this, "Выберите файл", QDir::currentPath(), "Cpp and Header Files (*.*)");

    // очистка списка
    ui->list_selected_files->clear();

    // проверка на пустую директорию
    if (files_path.size() == 0)
        return;

    qDebug() << files_path;

    fillSelecteFilesTable(files_path, ui);

}

void MainWindow::on_list_selected_files_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}




