#ifndef WORKWITHDB_H
#define WORKWITHDB_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>

#include "mainwindow.h"

#endif // WORKWITHDB_H

// открытие базы данных
bool tryToOpenDB(QSqlDatabase, QString);
