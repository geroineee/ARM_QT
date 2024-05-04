#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "realization/workWithDB.h"

#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QMessageBox>

// попытка отрыть файл, если такого нет, то он создается по пути file_path
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

// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read
// проверка на установленную кодировку файла
bool is_ANSI(QByteArray data)
{
    if (data[0] == '\xEF') // utf-8 со спецефикацией (цифровая подпись)
    {
        return 0;
    }

    QByteArray alphs;
    alphs.append(QString("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнпорстуфхцчшщъыьэюя").toLocal8Bit());

    for (QChar alph : data)
    {
        for (QChar alph_alph : alphs)
        {
            if (alph == alph_alph)
            {
                return 1;
            }
        }
    }
    return 0;
}

// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read
void readFromFile(QString current_path, QString& text_code)
{
    QFile *file;
    file = tryToOpenFile(current_path);
    if (file == nullptr)
        return;

    QByteArray data = file->readAll();
    if (is_ANSI(data))
    {
        text_code = QString::fromLocal8Bit(data); // ANSI (1251)
    }
    else
    {
        text_code = QString::fromUtf8(data); // utf-8 и utf-8 со спецификацией
    }
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

void fillSelecteFilesTable(QStringList& paths, Ui::MainWindow* ui)
{
    QStringList temp_list_path;
    for (const QString& file_path : qAsConst(paths))
    {
        QString file_name = getFIleName(file_path);
        int extension = isCppOrHeader(file_name);
        if (extension)
        {
            temp_list_path.append(file_path);
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
            QListWidgetItem *item2 = new QListWidgetItem(QIcon(image_path), file_name);
            ui->list_files->addItem(item);
            ui->list_selected_files->addItem(item2);
        }
    }
    paths = temp_list_path; // чтобы не было лишних путей
}

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
    fillSelecteFilesTable(files_path, ui);
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
