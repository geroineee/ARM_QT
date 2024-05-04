#include "utils.h"


//// проверка расширения файла: 1 - .cpp \ 2 - .h \ 0 - другое
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

// попытка отрыть файл, если такого нет, то он создается по пути file_path
QFile* tryToOpenFile(QString file_path)
{
    QFile *file = new QFile;
    file->setFileName(file_path);
    if (!file->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
        return nullptr;
    }
    return file;
}


// запись в файл, находящегося по пути path_to_file, данных data_to_write
void writeToFile(QString path_to_file, QString data_to_write)
{
    QTextStream writeStream;
    QFile *file;
    file = tryToOpenFile(path_to_file);
    if (file == nullptr)
        return;
    writeStream.setDevice(file);
    writeStream << data_to_write;
    file->close();
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

// заполнение окна с выбранными файлами
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

// проверка наличие кириллицы в путях
bool isCyrillic (QStringList files_path)
{
    QString alphabets = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнпорстуфхцчшщъыьэюя";
    for (const QString& file_path : qAsConst(files_path))
    {
        for (int index_alph = file_path.size()-1; index_alph > 0; index_alph--)
        {
            for (const QChar& alphs : qAsConst(alphabets))
            {
                if (file_path[index_alph] == alphs)
                    return 1;
            }
        }
    }
    return 0;
}

// удаление всех файлов с именами file_names, которые лежат по пути current_path
void delete_file(QString current_path, QStringList file_names)
{
    QString del_command = "@echo off\n"
                          "chcp 1251 > null.txt\n"
                          "cd /D " + current_path + "\n";
    for (const QString& file_name : qAsConst(file_names))
    {
        del_command.append("del " + file_name + "\n");
    }
    del_command.append("del null.txt\ndel delete_bat.bat\nexit");

    writeToFile(current_path + "delete_bat.bat", del_command);
    QProcess process_del;
    process_del.start(current_path + "delete_bat.bat");
    process_del.waitForFinished();
}

// получает список путей до файлов, и возвращает список имен файлов .cpp по этим путям
QStringList get_name_from_path(QStringList paths)
{
    QStringList temp_name;
    for (QString path : paths)
    {
        if (path[path.size()-1] == "p")
        {
            int index;
            for (index = path.size()-1; index > 0 && path[index] != "/"; index--);
            path.remove(0, index+1);
            temp_name.append(path);
        }
    }
    return temp_name;
}
