#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "databasemanager.h"
#include "album.h"

AlbumDao::AlbumDao(QSqlDatabase &database) : m_database(database)
{

}

void AlbumDao::init() const
{
    if(!m_database.tables().contains("albums"))
    {
        //Create an album table
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
        DatabaseManager::instance().debugQuery(query);
    }
}

void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
    DatabaseManager::instance().debugQuery(query);
}

void AlbumDao::updateAlbum(Album &album) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
    DatabaseManager::instance().debugQuery(query);
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::instance().debugQuery(query);
}

albumContainer AlbumDao::albums() const
{
    std::unique_ptr<std::vector<std::unique_ptr<Album> > > albumsVector(new std::vector<std::unique_ptr<Album>>());
    QSqlQuery query("SELECT * FROM albums", m_database);

    query.exec();
    DatabaseManager::instance().debugQuery(query);

    while(query.next())
    {
        auto currentAlbum = std::make_unique<Album>();
        currentAlbum->setName(query.value("name").toString());
        currentAlbum->setId(query.value("id").toInt());
        albumsVector->push_back(std::move(currentAlbum));
    }

    return albumsVector;
}


