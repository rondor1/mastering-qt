#include "picturedao.h"
#include "picture.h"

#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

PictureDao::PictureDao(QSqlDatabase &database) : m_database(database)
{

}

void PictureDao::init() const
{
    if(!m_database.tables().contains("pictures"))
    {
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE pictures (id INTEGER PRIMARY KEY AUTOINCREMENT, album_id INTEGER, url TEXT)");
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    QSqlQuery query(m_database);
    query.prepare(QString("INSERT INTO pictures ")
                  +" (album_id, url)"
                  + " VALUES ("
                  + ":album_id, "
                  + ":url)");
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.fileUrl());

    query.exec();
    DatabaseManager::instance().debugQuery(query);

    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM pictures WHERE album_id = (:id)");
    query.bindValue("(:id)", id);
    query.exec();
    DatabaseManager::instance().debugQuery(query);
}

void PictureDao::removePictureFromAlbum(int albumId)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");
    query.bindValue("(:album_id)", albumId);
    query.exec();
    DatabaseManager::instance().debugQuery(query);
}

pictureContainer PictureDao::picturesFromAlbum(int albumId) const
{
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(new std::vector<std::unique_ptr<Picture>>());
    QSqlQuery query(m_database);

    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue("(:album_id)", albumId);
    DatabaseManager::instance().debugQuery(query);

    while(query.next())
    {
        std::unique_ptr<Picture> currentPicture(new Picture);
        currentPicture->setAlbumId(albumId);
        currentPicture->setId(albumId);
        currentPicture->setFileUrl(query.value(":url").toString());
        list->push_back(std::move(currentPicture));
    }

    return list;
}
