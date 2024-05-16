#include "realization/database_operations.h"
#include "realization/utils.h"

#include "mainwindow.h"
#include "testwindow.h"


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
        if (!areListsEqual(database.tables(), QStringList{"Variants", "sqlite_sequence", "Tests", "LabWork"}))
        {
            qDebug() << database.tables() << "->" << QStringList{"sqlite_sequence", "Tests", "LabWork", "Variants"};
            database.exec("CREATE TABLE LabWork (id INTEGER, PRIMARY KEY(id, AUTOINCREMENT), name TEXT UNIQUE, description TEXT,)");
            database.exec("CREATE TABLE Variants (id INTEGER PRIMARY KEY AUTOINCREMENT, labwork_id INTEGER, conditions TEXT, number_var INTEGER, FOREIGN KEY (labwork_id) REFERENCES LabWork(id));");
            database.exec("CREATE TABLE Tests (id INTEGER PRIMARY KEY AUTOINCREMENT, variant_id INTEGER, input_data TEXT, output_data TEXT, FOREIGN KEY (variant_id) REFERENCES Variants(id));");
            qDebug() << "Таблицы созданы.";
        }
    }
    return true;
}

// получение рузультата запроса
QVariant getResult(QString query)
{
    QSqlQuery q(query);
    if (q.next())
    {
        return q.value(0);
    }
    return -1;
}

// нахождение первого свободного варианта
int getNextFreeNumberVar(QSqlDatabase& db, int labworkId)
{
    QSqlQuery query(db);
    query.prepare("SELECT MAX(number_var) + 1 FROM Variants WHERE labwork_id = :labwork_id");
    query.bindValue(":labwork_id", labworkId);

    if (!query.exec())
    {
        qWarning() << "Ошибка при выполнении запроса:" << query.lastError().text();
        return -1;
    }

    if (query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        // Если нет вариантов для заданного labwork_id, возвращаем 1
        return 1;
    }
}

// Нахождение первого свободного id в таблице
int getNextAvailableId(QSqlDatabase& db, QString table, QString field)
{
    QSqlQuery query(db);
    query.prepare("SELECT " + field + " FROM " + table + " ORDER BY " + field + " DESC LIMIT 1");

    if (!query.exec())
    {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
        return -1; // Возвращаем -1 или другое значение, указывающее на ошибку
    }

    if (query.next())
    {
        int lastId = query.value(0).toInt();
        for (int i = 1; i <= lastId; ++i)
        {
            query.prepare("SELECT " + field + " FROM " + table + " WHERE " + field + " = :id");
            query.bindValue(":id", i);
            if (!query.exec() || !query.next())
            {
                return i; // Возвращаем первый свободный id
            }
        }
        return lastId + 1; // Если все id от 1 до lastId заняты, возвращаем следующий id
    }
    else
    {
        // Если нет записей, возвращаем следующий id, который был бы автоматически сгенерирован
        return 1;
    }
}

// создание готового запроса для БД
QString makeInsertQuery(QString table, QStringList columns, QStringList data, QSqlDatabase& db)
{
    setToQuote(data);
    int id = getNextAvailableId(db, table, "id");
    QString query = "INSERT INTO " + table + "(id, " + columns.join(", ") + ") "
                    "VALUES ('" + QString::number(id) + "', " + data.join(", ") + ");";
    return query;
}

// Обновление данных в базе данных
QString updateData(QString table, QStringList columns, QStringList data, QString condition)
{
    setToQuote(data);
    QString query = "UPDATE " + table + " SET ";
    for (int i = 0; i < columns.size(); ++i)
    {
        query += columns[i] + " = " + data[i];
        if (i < columns.size() - 1)
            query += ", ";
    }
    query += " WHERE " + condition + ";";
    return query;
}

// Функция для определения существует ли запись с таким именем в базе данных
bool existsRecord(QString table, QString column, QString value)
{
    QString q = "SELECT COUNT(*) FROM " + table + " WHERE " + column + " = '" + value + "';";

    QSqlQuery query(q);
    if (query.lastError().type() != QSqlError::NoError)
    {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
        return false;
    }

    // Проверка результата запроса
    if (query.next())
    {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

// Функция для получения информации из поля
QString getDBDataQuery(QString table, QString data, QString column, QString column_condition)
{
    QString query = "SELECT " + data + " FROM " + table + " WHERE "
            + column + " = '" + column_condition + "';";
    return query;
}
