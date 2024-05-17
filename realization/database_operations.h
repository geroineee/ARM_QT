#ifndef DATABASE_OPERATIONS_H
#define DATABASE_OPERATIONS_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QVariant>
#include <QVector>

// открытие базы данных
bool tryToOpenDB(QSqlDatabase, QString);

// получение рузультата запроса
QVariant getResult(QString query);

// нахождение первого своббодного варианта
int getNextFreeNumberVar(QSqlDatabase& db, int labworkId);

// Нахождение первого свободного id в таблице
int getNextAvailableId(QSqlDatabase& db, QString table, QString field);

// создание готового запроса для БД
QString makeInsertQuery(QString table, QStringList columns, QStringList data, QSqlDatabase& db);

// Обновление данных в базе данных
QString updateData(QString table, QStringList columns, QStringList data, QString condition);

// Функция для определения существует ли запись с таким именем в базе данных
bool existsRecord(QString table, QString column, QString value);

// Функция для получения информации из поля
QString getDBDataQuery(QString table, QString data, QString column, QString column_condition);

// Функция для получения информации из поля (несколько условий)
QString getDBDataQuery(QString table, QString data, QStringList column, QStringList column_condition);

// получение всех данных, с нужным полем
QVector<QVariantList> getAllInTableWhere(QSqlDatabase db, QString table, QString field, QString condition, bool NotEqual = false);

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList&);


#endif // DATABASE_OPERATIONS_H

