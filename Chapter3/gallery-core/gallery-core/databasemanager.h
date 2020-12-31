#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>

class QSqlDatabase;


const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();

private:
    DatabaseManager(const DatabaseManager& db);
    DatabaseManager& operator=(const DatabaseManager& rhs);
    DatabaseManager();

private:
    QSqlDatabase* m_database;
};

#endif // DATABASEMANAGER_H
