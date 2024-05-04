#include "realization/database_operations.h"

#include "mainwindow.h"


// открытие базы данных
bool tryToOpenDB(QSqlDatabase database, QString db_name)
{
    database.setDatabaseName(QDir::currentPath() + "/" + db_name + ".db");

    if (database.open())
    {
        qDebug() << "База данных успешно открыта.";
    }
    else
    {
        qDebug() << "Ошибка открытия базы данных:\n" + database.lastError().text();
        return false;
    }

    // проверка на наличие нужных таблиц
    if (db_name == "Lab_works")
    {
        if (database.tables() != QStringList{"sqlite_sequence", "Tests", "LabWork", "Variants"})
        {
            database.exec("CREATE TABLE LabWork (id INTEGER, PRIMARY KEY(id), name TEXT UNIQUE, description TEXT,)");
            database.exec("CREATE TABLE Variants (id INTEGER PRIMARY KEY AUTOINCREMENT, labwork_id INTEGER, conditions TEXT, FOREIGN KEY (labwork_id) REFERENCES LabWork(id));");
            database.exec("CREATE TABLE Tests (id INTEGER PRIMARY KEY AUTOINCREMENT, variant_id INTEGER, input_data TEXT, output_data TEXT, FOREIGN KEY (variant_id) REFERENCES Variants(id));");
            qDebug() << "Таблицы созданы.";
        }
    }

    return true;
}

// заключение в одинарные кавычки всех элементов списка
void setToQuote(QStringList& data)
{
    for (int i = 0; i < data.size(); i++)
    {
       data[i] = "'" + data[i] + "'";
    }
}

// создание готового запроса для БД
QString makeInsertQuery(QString table, QStringList columns, QStringList data)
{
/*
    INSERT INTO Products(ProductName, Manufacturer, ProductCount, Price)
    VALUES ('iPhone X', 'Apple', 5, 76000);
*/
    setToQuote(data);
    QString query = "INSERT INTO " + table + "(" + columns.join(", ") + ") "
                    "VALUES (" + data.join(", ") + ");";

    return query;
}
