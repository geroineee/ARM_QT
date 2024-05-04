#ifndef WORKWITHDB_H
#define WORKWITHDB_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>

#include "mainwindow.h"

#endif // WORKWITHDB_H

// открытие базы данных
bool tryToOpenDB(QSqlDatabase, QString);

// создание готового запроса для БД
QString makeInsertQuery(QString, QStringList, QStringList);

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList&);
