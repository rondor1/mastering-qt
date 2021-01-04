#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>

class QSqlDatabase;
class QSqlQuery;

#include "albumdao.h"

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    void debugQuery(const QSqlQuery& query);

private:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    QSqlDatabase* m_database;

public:
    const AlbumDao m_albumDao;
};

#endif // DATABASEMANAGER_H
