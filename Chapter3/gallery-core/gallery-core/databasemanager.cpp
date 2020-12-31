#include "databasemanager.h"

#include <QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager()
{

}
