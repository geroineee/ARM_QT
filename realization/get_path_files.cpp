#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QMessageBox>

QStringList files_path;

QFile* tryToOpenFile(QString file_path)
{
    QFile *file = new QFile;
    file->setFileName(file_path);
    if (!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
        return nullptr;
    }
    return file;
}

void readFromFile(QString current_path, QString& text_code)
{
    //QString data;
    QFile *file;
    file = tryToOpenFile(current_path);
    if (file == nullptr)
        return;
    text_code = QString::fromLocal8Bit(file->readAll());
    //text_code = QString(data);
    file->close();
}

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
        int extension = isCppOrHeader(file_name);
        if (extension)
        {
            QString image_path;
            if (extension == 1)
            {
                image_path = ":/img/image/cpp_file.png";
            }
            else if (extension == 2)
            {
                image_path = ":/img/image/h_file.png";
            }
            QListWidgetItem *item = new QListWidgetItem(QIcon(image_path), file_name);
            ui->list_selected_files->addItem(item);
        }
    }
}

void MainWindow::on_button_get_path_files_clicked()
{
    // получения пути до файлов
    files_path = QFileDialog::getOpenFileNames(this, "Выберите файл", QDir::currentPath(), "Cpp and Header Files (*.*)");

    // очистка списка
    ui->list_selected_files->clear();

    // проверка на пустую директорию
    if (files_path.size() == 0)
        return;

    fillSelecteFilesTable(files_path, ui);

}

void MainWindow::on_list_selected_files_itemDoubleClicked(QListWidgetItem *item)
{
    QString text_code, path = files_path[0];
    int index;
    for (index = path.size()-1; index > 0 && path[index] != "/"; index--);
    path.remove(index+1, path.size()-index).append(item->text());
    readFromFile(path, text_code);
    code_window = new usercodewindow(this, text_code);
    code_window->setWindowTitle(item->text());
    code_window->show();
}




