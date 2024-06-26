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

// попытка отрыть файл, если такого нет, то он создается по пути file_path
QFile* tryToOpenFile(QString file_path, bool isTranc)
{
    QFile *file = new QFile;
    file->setFileName(file_path);
    if (isTranc)
    {
        if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            delete file;
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
            return nullptr;
        }
    }
    else if (!file->open(QIODevice::ReadWrite))
    {
        delete file;
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);
        return nullptr;
    }
    return file;
}

// запись в файл, находящегося по пути path_to_file, данных data_to_write
void writeToFile(QString path_to_file, QString data_to_write, bool isTrunc)
{
    QTextStream writeStream;
    QFile *file;
    file = tryToOpenFile(path_to_file, isTrunc);
    if (file == nullptr)
        return;
    writeStream.setDevice(file);
    writeStream << data_to_write;
    file->close();
    delete file;
}

// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read
void readFromFile(QString path_to_file, QString& text_code)
{
    QFile *file;
    file = tryToOpenFile(path_to_file);
    if (file == nullptr)
        return;

    QByteArray data = file->readAll();
    text_code = QString::fromUtf8(data); // utf-8 и utf-8 со спецификацией
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
void fillSelecteFilesTable(QStringList& paths, QListWidget* list)
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
            list->addItem(item);
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
                          "chcp 1251 > null\n"
                          "cd /D " + current_path + "\n";
    for (const QString& file_name : qAsConst(file_names))
    {
        del_command.append("del " + file_name + "\n");
    }
    del_command.append("\n del start_compile.bat\ndel null\ndel delete_bat.bat\nexit");

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

bool areListsEqual(const QStringList& list1, const QStringList& list2)
{
    return list1.size() == list2.size() && std::includes(list1.begin(), list1.end(), list2.begin(), list2.end());
}

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList& data)
{
    for (int i = 0; i < data.size(); i++)
    {
       data[i] = "'" + data[i] + "'";
    }
}

// Компилирует код | directory_path передается с "/" |
void compile_code(QString directory_path, QStringList file_names, bool isTest)
{
    QString compiled_files = "";
    for (const QString& file : qAsConst(file_names))
    {
        compiled_files.append('"' + file + '"');
        compiled_files.append(' ');
    }
    compiled_files.chop(1);

    QString str = "";
    if (!isTest)
        str = "user_main_code.exe < user_input.txt\n"
              "del user_main_code.exe\n";

    // открытие и запись в start_compile.bat
    QString command = "@echo off\n"
                      "chcp 65001 > null\n"
                      "cd /D " + directory_path + "\n"
                      "g++ -Wall " + compiled_files + " -o user_main_code.exe\n"
                      + str +
                      "exit";
    writeToFile(directory_path + "start_compile.bat", command);
}

// Создает батник для проверки тестов
void bat_for_check_test(QString directory_path)
{
    // открытие и запись в start_check_test.bat
    QString command = "@echo off\n"
                      "chcp 65001 > null\n"
                      "cd /D " + directory_path + "\n"
                      "user_main_code.exe < user_input.txt\n"
                      "exit";
    writeToFile(directory_path + "start_check_test.bat", command);
}

// Получение текущей даты и времени
QString getCurrentDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("HH:mm dd.MM.yyyy");
    return formattedDateTime;
}
