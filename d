warning: in the working copy of 'realization/database_operations.h', LF will be replaced by CRLF the next time Git touches it
[1mdiff --git a/ARM_QT.pro b/ARM_QT.pro[m
[1mindex b12af76..192767d 100644[m
[1m--- a/ARM_QT.pro[m
[1m+++ b/ARM_QT.pro[m
[36m@@ -11,15 +11,17 @@[m [mCONFIG += c++11[m
 SOURCES += \[m
     main.cpp \[m
     mainwindow.cpp \[m
[32m+[m[32m    realization/database_operations.cpp \[m
     realization/tab_files.cpp \[m
     realization/tab_only_code.cpp \[m
[31m-    realization/workWithDB.cpp \[m
[32m+[m[32m    realization/utils.cpp \[m
     testwindow.cpp \[m
     textwindow.cpp[m
 [m
 HEADERS += \[m
     mainwindow.h \[m
[31m-    realization/workWithDB.h \[m
[32m+[m[32m    realization/database_operations.h \[m
[32m+[m[32m    realization/utils.h \[m
     testwindow.h \[m
     textwindow.h[m
 [m
[1mdiff --git a/bin/Lab_works.db b/bin/Lab_works.db[m
[1mindex d7d0cfd..3a45106 100644[m
Binary files a/bin/Lab_works.db and b/bin/Lab_works.db differ
[1mdiff --git a/mainwindow.cpp b/mainwindow.cpp[m
[1mindex a9b1365..4292599 100644[m
[1m--- a/mainwindow.cpp[m
[1m+++ b/mainwindow.cpp[m
[36m@@ -1,10 +1,7 @@[m
 #include "mainwindow.h"[m
 #include "ui_mainwindow.h"[m
 [m
[31m-//#include "testwindow.h"[m
[31m-//#include "ui_testwindow.h"[m
[31m-[m
[31m-#include "realization//tab_only_code.cpp"[m
[32m+[m[32m#include "realization/tab_files.cpp"[m
 [m
 MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)[m
 {[m
[36m@@ -75,3 +72,31 @@[m [mvoid MainWindow::receiveQuery(QString text_query)[m
     qDebug() << "Запрос: " << text_query;[m
     database.exec(text_query);[m
 }[m
[32m+[m
[32m+[m[32mvoid MainWindow::choose_files()[m
[32m+[m[32m{[m
[32m+[m[32m    QStringList temp_paths; // нужен, если пользователь случайно нажал (не хотел выбирать файлы), чтобы список не очищался[m
[32m+[m[32m    QString current_path; // для запоминания последней директории[m
[32m+[m
[32m+[m[32m    if (files_path.isEmpty())[m
[32m+[m[32m        current_path = QDir::currentPath();[m
[32m+[m
[32m+[m[32m    // выбор файла[m
[32m+[m[32m    temp_paths = QFileDialog::getOpenFileNames(this, "Выберите файл", current_path, "Cpp and Header Files (*.*)");[m
[32m+[m
[32m+[m[32m    // проверка на пустую директорию[m
[32m+[m[32m    if (temp_paths.isEmpty())[m
[32m+[m[32m    {[m
[32m+[m[32m        return;[m
[32m+[m[32m    }[m
[32m+[m[32m    files_path = temp_paths;[m
[32m+[m
[32m+[m[32m    current_path = files_path[0];[m
[32m+[m
[32m+[m[32m    // очистка listWidget[m
[32m+[m[32m    ui->list_selected_files->clear();[m
[32m+[m[32m    ui->list_files->clear();[m
[32m+[m
[32m+[m[32m    // заполнение списка[m
[32m+[m[32m    fillSelecteFilesTable(files_path, ui);[m
[32m+[m[32m}[m
[1mdiff --git a/mainwindow.h b/mainwindow.h[m
[1mindex 76dee78..4f76e20 100644[m
[1m--- a/mainwindow.h[m
[1m+++ b/mainwindow.h[m
[36m@@ -10,9 +10,12 @@[m
 [m
 #include <QSqlDatabase>[m
 #include <QSqlError>[m
[32m+[m[32m#include <QFileDialog>[m
 #include <QSqlTableModel>[m
 #include <QDebug>[m
 [m
[32m+[m[32m#include "realization/database_operations.h"[m
[32m+[m[32m//#include "realization/utils.h"[m
 [m
 QT_BEGIN_NAMESPACE[m
 namespace Ui { class MainWindow; }[m
[36m@@ -41,7 +44,6 @@[m [mprivate slots:[m
     void on_button_compile_file_clicked();[m
 [m
 private:[m
[31m-    QStringList files_path;[m
     void choose_files();[m
     void for_button_compile(bool isWorkWithFile);[m
     void showUserCode(QListWidget*, QListWidgetItem*);[m
[36m@@ -50,7 +52,10 @@[m [mprivate:[m
     usercodewindow *code_window;[m
     Ui::MainWindow *ui;[m
 [m
[31m-public:[m
[32m+[m[32m    // пути до выбранных файлов[m
[32m+[m[32m    QStringList files_path;[m
[32m+[m
[32m+[m[32m    // для работы с базой данных[m
     QSqlDatabase database;[m
     QSqlTableModel *db_model;[m
 };[m
[1mdiff --git a/realization/database_operations.cpp b/realization/database_operations.cpp[m
[1mindex bda1b3f..2382b5e 100644[m
[1m--- a/realization/database_operations.cpp[m
[1m+++ b/realization/database_operations.cpp[m
[36m@@ -1,4 +1,6 @@[m
[31m-#include "realization/workWithDB.h"[m
[32m+[m[32m#include "realization/database_operations.h"[m
[32m+[m
[32m+[m[32m#include "mainwindow.h"[m
 [m
 [m
 // открытие базы данных[m
[1mdiff --git a/realization/database_operations.h b/realization/database_operations.h[m
[1mindex c825442..c88de7b 100644[m
[1m--- a/realization/database_operations.h[m
[1m+++ b/realization/database_operations.h[m
[36m@@ -1,14 +1,10 @@[m
[31m-#ifndef WORKWITHDB_H[m
[31m-#define WORKWITHDB_H[m
[32m+[m[32m#ifndef DATABASE_OPERATIONS_H[m
[32m+[m[32m#define DATABASE_OPERATIONS_H[m
 [m
 #include <QDir>[m
 #include <QDebug>[m
 #include <QSqlQuery>[m
 [m
[31m-#include "mainwindow.h"[m
[31m-[m
[31m-#endif // WORKWITHDB_H[m
[31m-[m
 // открытие базы данных[m
 bool tryToOpenDB(QSqlDatabase, QString);[m
 [m
[36m@@ -17,3 +13,7 @@[m [mQString makeInsertQuery(QString, QStringList, QStringList);[m
 [m
 // заключение в одинарные кавычки всех элементов списка[m
 void setToQuote(QStringList&);[m
[32m+[m
[32m+[m
[32m+[m[32m#endif // DATABASE_OPERATIONS_H[m
[41m+[m
[1mdiff --git a/realization/tab_files.cpp b/realization/tab_files.cpp[m
[1mindex 7dfe822..25ceda7 100644[m
[1m--- a/realization/tab_files.cpp[m
[1m+++ b/realization/tab_files.cpp[m
[36m@@ -1,7 +1,7 @@[m
 #include "mainwindow.h"[m
 #include "ui_mainwindow.h"[m
 [m
[31m-#include "realization/workWithDB.h"[m
[32m+[m[32m#include "realization/database_operations.h"[m
 [m
 #include <QFileDialog>[m
 #include <QFile>[m
[1mdiff --git a/realization/tab_only_code.cpp b/realization/tab_only_code.cpp[m
[1mindex 56370f0..cd6d1ed 100644[m
[1m--- a/realization/tab_only_code.cpp[m
[1m+++ b/realization/tab_only_code.cpp[m
[36m@@ -1,7 +1,7 @@[m
 #include "mainwindow.h"[m
 #include "ui_mainwindow.h"[m
 [m
[31m-#include "realization/workWithDB.h"[m
[32m+[m[32m#include "realization/database_operations.h"[m
 [m
 #include <Windows.h>[m
 [m
[1mdiff --git a/realization/utils.cpp b/realization/utils.cpp[m
[1mnew file mode 100644[m
[1mindex 0000000..4120c2e[m
[1m--- /dev/null[m
[1m+++ b/realization/utils.cpp[m
[36m@@ -0,0 +1,190 @@[m
[32m+[m[32m#include "utils.h"[m
[32m+[m
[32m+[m
[32m+[m[32m// попытка отрыть файл, если такого нет, то он создается по пути file_path[m
[32m+[m[32mQFile* tryToOpenFile(QString file_path)[m
[32m+[m[32m{[m
[32m+[m[32m    QFile *file = new QFile;[m
[32m+[m[32m    file->setFileName(file_path);[m
[32m+[m[32m    if (!file->open(QIODevice::ReadWrite))[m
[32m+[m[32m    {[m
[32m+[m[32m        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при открытии файла по пути:\n" + file_path);[m
[32m+[m[32m        return nullptr;[m
[32m+[m[32m    }[m
[32m+[m[32m    return file;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read[m
[32m+[m[32mvoid readFromFile(QString current_path, QString& text_code)[m
[32m+[m[32m{[m
[32m+[m[32m    QFile *file;[m
[32m+[m[32m    file = tryToOpenFile(current_path);[m
[32m+[m[32m    if (file == nullptr)[m
[32m+[m[32m        return;[m
[32m+[m
[32m+[m[32m    QByteArray data = file->readAll();[m
[32m+[m[32m    if (is_ANSI(data))[m
[32m+[m[32m    {[m
[32m+[m[32m        text_code = QString::fromLocal8Bit(data); // ANSI (1251)[m
[32m+[m[32m    }[m
[32m+[m[32m    else[m
[32m+[m[32m    {[m
[32m+[m[32m        text_code = QString::fromUtf8(data); // utf-8 и utf-8 со спецификацией[m
[32m+[m[32m    }[m
[32m+[m[32m    file->close();[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// Получение имени файла с расширением[m
[32m+[m[32mQString getFIleName(QString path)[m
[32m+[m[32m{[m
[32m+[m[32m    int pos = path.size() - 1;[m
[32m+[m[32m    while (pos && path[pos] != "/")[m
[32m+[m[32m    {[m
[32m+[m[32m        pos--;[m
[32m+[m[32m    }[m
[32m+[m[32m    return path.remove(0, ++pos);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// заполнение окна с выбранными файлами[m
[32m+[m[32mvoid fillSelecteFilesTable(QStringList& paths, Ui::MainWindow* ui)[m
[32m+[m[32m{[m
[32m+[m[32m    QStringList temp_list_path;[m
[32m+[m[32m    for (const QString& file_path : qAsConst(paths))[m
[32m+[m[32m    {[m
[32m+[m[32m        QString file_name = getFIleName(file_path);[m
[32m+[m[32m        int extension = isCppOrHeader(file_name);[m
[32m+[m[32m        if (extension)[m
[32m+[m[32m        {[m
[32m+[m[32m            temp_list_path.append(file_path);[m
[32m+[m[32m            QString image_path;[m
[32m+[m[32m            if (extension == 1)[m
[32m+[m[32m            {[m
[32m+[m[32m                image_path = ":/img/image/cpp_file.png";[m
[32m+[m[32m            }[m
[32m+[m[32m            else if (extension == 2)[m
[32m+[m[32m            {[m
[32m+[m[32m                image_path = ":/img/image/h_file.png";[m
[32m+[m[32m            }[m
[32m+[m[32m            QListWidgetItem *item = new QListWidgetItem(QIcon(image_path), file_name);[m
[32m+[m[32m            QListWidgetItem *item2 = new QListWidgetItem(QIcon(image_path), file_name);[m
[32m+[m[32m            ui->list_files->addItem(item);[m
[32m+[m[32m            ui->list_selected_files->addItem(item2);[m
[32m+[m[32m        }[m
[32m+[m[32m    }[m
[32m+[m[32m    paths = temp_list_path; // чтобы не было лишних путей[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// проверка расширения файла: 1 - .cpp \ 2 - .h \ 0 - другое[m
[32m+[m[32mint isCppOrHeader(QString fileName)[m
[32m+[m[32m{[m
[32m+[m[32m    int pos = fileName.size() - 1;[m
[32m+[m[32m    while (pos && fileName[pos] != ".")[m
[32m+[m[32m    {[m
[32m+[m[32m        pos--;[m
[32m+[m[32m    }[m
[32m+[m[32m    if (fileName.remove(0, ++pos) == "cpp")[m
[32m+[m[32m        return 1;[m
[32m+[m[32m    else if (fileName == "h")[m
[32m+[m[32m        return 2;[m
[32m+[m[32m    else[m
[32m+[m[32m        return 0;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// проверка на установленную кодировку файла[m
[32m+[m[32mbool is_ANSI(QByteArray data)[m
[32m+[m[32m{[m
[32m+[m[32m    if (data[0] == '\xEF') // utf-8 со спецефикацией (цифровая подпись)[m
[32m+[m[32m    {[m
[32m+[m[32m        return 0;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    QByteArray alphs;[m
[32m+[m[32m    alphs.append(QString("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнпорстуфхцчшщъыьэюя").toLocal8Bit());[m
[32m+[m
[32m+[m[32m    for (QChar alph : data)[m
[32m+[m[32m    {[m
[32m+[m[32m        for (QChar alph_alph : alphs)[m
[32m+[m[32m        {[m
[32m+[m[32m            if (alph == alph_alph)[m
[32m+[m[32m            {[m
[32m+[m[32m                return 1;[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m    }[m
[32m+[m[32m    return 0;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// проверка наличие кириллицы в путях[m
[32m+[m[32mbool isCyrillic (QStringList files_path)[m
[32m+[m[32m{[m
[32m+[m[32m    QString alphabets = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнпорстуфхцчшщъыьэюя";[m
[32m+[m[32m    for (const QString& file_path : qAsConst(files_path))[m
[32m+[m[32m    {[m
[32m+[m[32m        for (int index_alph = file_path.size()-1; index_alph > 0; index_alph--)[m
[32m+[m[32m        {[m
[32m+[m[32m            for (const QChar& alphs : qAsConst(alphabets))[m
[32m+[m[32m            {[m
[32m+[m[32m                if (file_path[index_alph] == alphs)[m
[32m+[m[32m                    return 1;[m
[32m+[m[32m            }[m
[32m+[m[32m        }[m
[32m+[m[32m    }[m
[32m+[m[32m    return 0;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// удаление всех файлов с именами file_names, которые лежат по пути current_path[m
[32m+[m[32mvoid delete_file(QString current_path, QStringList file_names)[m
[32m+[m[32m{[m
[32m+[m[32m    QString del_command = "@echo off\n"[m
[32m+[m[32m                          "chcp 1251 > null.txt\n"[m
[32m+[m[32m                          "cd /D " + current_path + "\n";[m
[32m+[m[32m    for (const QString& file_name : qAsConst(file_names))[m
[32m+[m[32m    {[m
[32m+[m[32m        del_command.append("del " + file_name + "\n");[m
[32m+[m[32m    }[m
[32m+[m[32m    del_command.append("del null.txt\ndel delete_bat.bat\nexit");[m
[32m+[m
[32m+[m[32m    writeToFile(current_path + "delete_bat.bat", del_command);[m
[32m+[m[32m    QProcess process_del;[m
[32m+[m[32m    process_del.start(current_path + "delete_bat.bat");[m
[32m+[m[32m    process_del.waitForFinished();[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// Компилирует код | directory_path передается с "/" |[m
[32m+[m[32mvoid compile_code(QProcess& process, QString directory_path, QStringList file_names)[m
[32m+[m[32m{[m
[32m+[m[32m    QString compiled_files = "";[m
[32m+[m[32m    for (const QString& file : qAsConst(file_names))[m
[32m+[m[32m    {[m
[32m+[m[32m        compiled_files.append(file + " ");[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    // открытие и запись в start_compile.bat[m
[32m+[m[32m    QString command = "@echo off\n"[m
[32m+[m[32m                      "chcp 65001 > null.txt\n"[m
[32m+[m[32m                      "cd /D " + directory_path + "\n"[m
[32m+[m[32m                      "g++ -g -Wall " + compiled_files + "-o user_main_code.exe\n"[m
[32m+[m[32m                      "user_main_code.exe < user_input.txt > user_output.txt\n"[m
[32m+[m[32m                      "del user_main_code.exe\n"[m
[32m+[m[32m                      "del null.txt\n"[m
[32m+[m[32m                      "del start_compile.bat\n"[m
[32m+[m[32m                      "exit";[m
[32m+[m[32m    writeToFile(directory_path + "start_compile.bat", command);[m
[32m+[m
[32m+[m[32m    // запуск start_compile.bat[m
[32m+[m[32m    process.start(directory_path + "start_compile.bat");[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// запись в файл, находящегося по пути path_to_file, данных data_to_write[m
[32m+[m[32mvoid writeToFile(QString path_to_file, QString data_to_write)[m
[32m+[m[32m{[m
[32m+[m[32m    QTextStream writeStream;[m
[32m+[m[32m    QFile *file;[m
[32m+[m[32m    file = tryToOpenFile(path_to_file);[m
[32m+[m[32m    if (file == nullptr)[m
[32m+[m[32m        return;[m
[32m+[m[32m    writeStream.setDevice(file);[m
[32m+[m[32m    writeStream << data_to_write;[m
[32m+[m[32m    file->close();[m
[32m+[m[32m}[m
[32m+[m
[1mdiff --git a/realization/utils.h b/realization/utils.h[m
[1mnew file mode 100644[m
[1mindex 0000000..87e7f70[m
[1m--- /dev/null[m
[1m+++ b/realization/utils.h[m
[36m@@ -0,0 +1,51 @@[m
[32m+[m[32m#ifndef UTILS_H[m
[32m+[m[32m#define UTILS_H[m
[32m+[m
[32m+[m[32m#include "mainwindow.h"[m
[32m+[m[32m#include "ui_mainwindow.h"[m
[32m+[m
[32m+[m[32m#include <QFileDialog>[m
[32m+[m[32m#include <QProcess>[m
[32m+[m[32m#include <QFile>[m
[32m+[m[32m#include <QByteArray>[m
[32m+[m[32m#include <QString>[m
[32m+[m[32m#include <QDebug>[m
[32m+[m[32m#include <QMessageBox>[m
[32m+[m
[32m+[m[32m#include <Windows.h>[m
[32m+[m
[32m+[m
[32m+[m[32m// попытка отрыть файл, если такого нет, то он создается по пути file_path[m
[32m+[m[32mQFile* tryToOpenFile(QString file_path);[m
[32m+[m
[32m+[m[32m// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read[m
[32m+[m[32mvoid readFromFile(QString current_path, QString& text_code);[m
[32m+[m
[32m+[m[32m// Получение имени файла с расширением[m
[32m+[m[32mQString getFIleName(QString path);[m
[32m+[m
[32m+[m[32m// удаление всех файлов с именами file_names, которые лежат по пути current_path[m
[32m+[m[32mvoid delete_file(QString current_path, QStringList file_names);\[m
[32m+[m
[32m+[m[32m// Компилирует код | directory_path передается с "/" |[m
[32m+[m[32mvoid compile_code(QProcess& process, QString directory_path, QStringList file_names);[m
[32m+[m
[32m+[m[32m// заполнение окна с выбранными файлами[m
[32m+[m[32mvoid fillSelecteFilesTable(QStringList& paths, Ui::MainWindow* ui);[m
[32m+[m
[32m+[m[32m// проверка на установленную кодировку файла[m
[32m+[m[32mbool is_ANSI(QByteArray data);[m
[32m+[m
[32m+[m[32m// проверка расширения файла: 1 - .cpp \ 2 - .h \ 0 - другое[m
[32m+[m[32mint isCppOrHeader(QString fileName);[m
[32m+[m
[32m+[m[32m// проверка наличие кириллицы в путях[m
[32m+[m[32mbool isCyrillic (QStringList files_path);[m
[32m+[m
[32m+[m[32m// запись в файл, находящегося по пути path_to_file, данных data_to_write[m
[32m+[m[32mvoid writeToFile(QString path_to_file, QString data_to_write);[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m[32m#endif // UTILS_H[m
[1mdiff --git a/testwindow.cpp b/testwindow.cpp[m
[1mindex 0855b56..247dd80 100644[m
[1m--- a/testwindow.cpp[m
[1m+++ b/testwindow.cpp[m
[36m@@ -5,7 +5,7 @@[m
 #include <QMessageBox>[m
 #include <QDebug>[m
 [m
[31m-#include "realization/workWithDB.h"[m
[32m+[m[32m#include "realization/database_operations.h"[m
 [m
 testwindow::testwindow(QWidget *parent) : QDialog(parent), ui(new Ui::testwindow)[m
 {[m
