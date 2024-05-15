#ifndef DATABASE_OPERATIONS_H
#define DATABASE_OPERATIONS_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>

// открытие базы данных
bool tryToOpenDB(QSqlDatabase, QString);

// Нахождение первого свободного id в таблице
int getNextAvailableId(QSqlDatabase& db, QString table);

// создание готового запроса для БД
QString makeInsertQuery(QString, QStringList, QStringList, QSqlDatabase&);

// Обновление данных в базе данных
QString updateData(QString table, QStringList columns, QStringList data, QString condition);

// Функция для определения существует ли запись с таким именем в базе данных
bool existsRecord(QString table, QString column, QString value);

// Функция для получения информации из поля
QString getDBDataQuery(QString table, QString data, QString column, QString column_condition);

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList&);


#endif // DATABASE_OPERATIONS_H

