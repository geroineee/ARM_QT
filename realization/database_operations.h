#ifndef DATABASE_OPERATIONS_H
#define DATABASE_OPERATIONS_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>

// открытие базы данных
bool tryToOpenDB(QSqlDatabase, QString);

// создание готового запроса для БД
QString makeInsertQuery(QString, QStringList, QStringList);

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList&);


#endif // DATABASE_OPERATIONS_H

