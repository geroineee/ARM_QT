#ifndef UTILS_H
#define UTILS_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QProcess>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QStandardItemModel>

#include <Windows.h>

// сравнение строковых списков на равенство
bool areListsEqual(const QStringList& list1, const QStringList& list2);

// попытка отрыть файл, если такого нет, то он создается по пути file_path
QFile* tryToOpenFile(QString file_path, bool isTrunc = false);

// считывание данных из файла, находящегося по пути path_to_file, и запись их в where_to_read
void readFromFile(QString current_path, QString& text_code);

// Получение имени файла с расширением
QString getFIleName(QString path);

// удаление всех файлов с именами file_names, которые лежат по пути current_path
void delete_file(QString current_path, QStringList file_names);\

// заполнение окна с выбранными файлами
void fillSelecteFilesTable(QStringList& paths, QListWidget* list);

// проверка расширения файла: 1 - .cpp \ 2 - .h \ 0 - другое
int isCppOrHeader(QString fileName);

// проверка наличие кириллицы в путях
bool isCyrillic (QStringList files_path);

// запись в файл, находящегося по пути path_to_file, данных data_to_write
void writeToFile(QString path_to_file, QString data_to_write, bool isTrunc = false);

// получает список путей до файлов, и возвращает список имен файлов .cpp по этим путям
QStringList get_name_from_path(QStringList paths);

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList& data);

// Компилирует код | directory_path передается с "/" |
void compile_code(QString directory_path, QStringList file_names, bool isTest = false);

// Создает батник для проверки тестов
void bat_for_check_test(QString directory_path);

// Получение текущей даты и времени
QString getCurrentDateTime();

#endif // UTILS_H
