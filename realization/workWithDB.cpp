#include "realization/workWithDB.h"


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

    QSqlQuery query;

    qDebug() << database.tables();

    // проверка на наличие нужных таблиц
    if (db_name == "Lab_works.db")
    {
        if (database.tables() != QStringList{"sqlite_sequence", "Tests", "LabWork", "Variants"})
        {
            query.exec("CREATE TABLE LabWork (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, description TEXT);");
            query.exec("CREATE TABLE Variants (id INTEGER PRIMARY KEY AUTOINCREMENT, labwork_id INTEGER, conditions TEXT, FOREIGN KEY (labwork_id) REFERENCES LabWork(id));");
            query.exec("CREATE TABLE Tests (id INTEGER PRIMARY KEY AUTOINCREMENT, variant_id INTEGER, input_data TEXT, output_data TEXT, FOREIGN KEY (variant_id) REFERENCES Variants(id));");
            qDebug() << "Таблицы созданы.";
        }
    }

    return true;
}
