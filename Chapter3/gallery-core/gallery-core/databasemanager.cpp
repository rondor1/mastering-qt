#include "databasemanager.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

DatabaseManager::~DatabaseManager()
{
    m_database->close();
    delete m_database;
}

DatabaseManager::DatabaseManager(const QString& path) : m_database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))), m_albumDao(*m_database), m_pictureDao(*m_database)
{
    m_database->setDatabaseName(path);
    m_database->open();

    m_albumDao.init();
    m_pictureDao.init();
}
