#include "realization/database_operations.h"
#include "realization/utils.h"

#include "mainwindow.h"
#include "testwindow.h"


// открытие базы данных
bool tryToOpenDB(QSqlDatabase database, QString db_name)
{
    database.setDatabaseName(QDir::currentPath() + "/" + db_name + ".db");

    if (!database.open())
    {
        qDebug() << "Ошибка открытия базы данных:\n" + database.lastError().text();
        return false;
    }

    // проверка на наличие нужных таблиц
    if (db_name == "Lab_works")
    {
        if (database.tables().size() != 6)
        {
            database.exec("CREATE TABLE LabWork (id	INTEGER, name TEXT UNIQUE, description TEXT,PRIMARY KEY(id AUTOINCREMENT))");
            database.exec("CREATE TABLE Variants (id INTEGER PRIMARY KEY AUTOINCREMENT, labwork_id INTEGER, conditions TEXT, number_var INTEGER, FOREIGN KEY (labwork_id) REFERENCES LabWork(id));");
            database.exec("CREATE TABLE Tests (id INTEGER PRIMARY KEY AUTOINCREMENT, variant_id INTEGER, input_data TEXT, output_data TEXT, FOREIGN KEY (variant_id) REFERENCES Variants(id));");
            database.exec("CREATE TABLE Person (id INTEGER,date TEXT, person_name TEXT, PRIMARY KEY(id AUTOINCREMENT))");
            database.exec("CREATE TABLE CheckedWorks (id INTEGER, person_id INTEGER, date TEXT, work_name TEXT, task TEXT, status TEXT, input_data TEXT, expected_output TEXT, output_data TEXT,PRIMARY KEY( id AUTOINCREMENT))");
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

    // Найти максимальный number_var для заданного labwork_id
    query.prepare("SELECT COALESCE(MAX(number_var), 0) FROM Variants WHERE labwork_id = :labworkId");
    query.bindValue(":labworkId", labworkId);

    if (!query.exec() || !query.next())
    {
        qWarning() << "Ошибка при выполнении запроса:" << query.lastError().text();
        return -1;
    }

    int lastVar = query.value(0).toInt();

    // Проверить каждый number_var от 1 до lastVar
    for (int i = 1; i <= lastVar + 1; ++i)
    {
        query.prepare("SELECT COUNT(*) FROM Variants WHERE labwork_id = :labworkId AND number_var = :numberVar");
        query.bindValue(":labworkId", labworkId);
        query.bindValue(":numberVar", i);

        if (!query.exec() || !query.next())
        {
            qWarning() << "Ошибка при выполнении запроса:" << query.lastError().text();
            return -1;
        }

        int count = query.value(0).toInt();
        if (count == 0)
        {
            return i; // возвращается первый свободный number_var
        }
    }

    // Если все number_var от 1 до lastVar заняты, возвращается следующий number_var
    return lastVar + 1;
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
    return getDBDataQuery(table, data, QStringList (column), QStringList(column_condition));
}

// Функция для получения информации из поля (несколько условий)
QString getDBDataQuery(QString table, QString data, QStringList column, QStringList column_condition)
{
    QString condition;
    for (int i = 0; i < column.size(); i++)
    {
        condition += " AND " + column[i] + " = '" + column_condition[i] + "'";
    }
    condition.remove(0, 5);

    QString query = "SELECT " + data + " FROM " + table + " WHERE ("
            + condition + ");";
    return query;
}

// получение всех данных, с нужным полем
QVector<QVariantList> getAllInTableWhere(QSqlDatabase db, QString table, QString field, QString condition, bool NotEqual)
{
    QSqlQuery query(db);
    QVector<QVariantList> result;

    // Формирование SQL запроса
    if (!NotEqual)
        query.prepare("SELECT * FROM " + table + " WHERE " + field + " = :cond");
    else
        query.prepare("SELECT * FROM " + table + " WHERE " + field + " != :cond");

    query.bindValue(":cond", condition);

    // Выполнение запроса
    if (query.exec())
    {
        // Считка результата
        while (query.next())
        {
            QVariantList row;
            for (int i = 0; i < query.record().count(); ++i)
            {
                row.append(query.value(i));
            }
            result.append(row);
        }
    }
    else
    {
        // Обработка ошибки выполнения запроса
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
    }

    return result;
}

// получение всех данных, с полемм, содержащем подстроку
QVector<QVariantList> getAllLIKE(QSqlDatabase db, QString table, QString field, QString substr)
{
    QSqlQuery query(db);
    QVector<QVariantList> result;

    // Формирование SQL запроса
    query.prepare("SELECT * FROM " + table + " WHERE " + field + " LIKE :substr");
    query.bindValue(":substr", substr);

    // Выполнение запроса
    if (query.exec())
    {
        // Считка результата
        while (query.next())
        {
            QVariantList row;
            for (int i = 0; i < query.record().count(); ++i)
            {
                row.append(query.value(i));
            }
            result.append(row);
        }
    }
    else
    {
        // Обработка ошибки выполнения запроса
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
    }

    return result;
}
