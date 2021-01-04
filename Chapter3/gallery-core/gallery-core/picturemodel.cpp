#include "picturemodel.h"

#include "album.h"
#include "albummodel.h"
#include "databasemanager.h"
#include "picture.h"

PictureModel::PictureModel(const AlbumModel &album, QObject *parent) : m_databaseManager(DatabaseManager::instance()),
    m_albumId(-1), m_pictures(new std::vector<std::unique_ptr<Picture>>())
{
    Q_UNUSED(parent);
    connect(&album, &AlbumModel::removeRow, this, &PictureModel::deletePicturesForAlbum);

}

QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<Picture> newPicture(new Picture(picture));
    m_databaseManager.m_pictureDao.addPictureInAlbum(m_albumId, *newPicture);
    m_pictures->push_back(std::move(newPicture));
    endInsertColumns();

    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_pictures->size();
}

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const Picture& picture = *m_pictures->at(index.row());

    switch(role)
    {
    case UrlRole:
        return picture.fileUrl();
        break;
    case FilePathRole:
        return picture.fileUrl().fileName();
    default:
        return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{

    if(row <0 || row >= rowCount() || count < 0 || (row+count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count-1);

    int countLeft = count;
    while(countLeft--)
    {
        const Picture& currentPicture = *m_pictures->at(row+count);
        m_databaseManager.m_pictureDao.removePicture(currentPicture.id());
    }
    m_pictures->erase(m_pictures->begin() + row, m_pictures->begin() + row + count);

    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PictureRole::FilePathRole] = "filepath";
    return roles;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    m_albumId = albumId;
    loadPictures(albumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    //Start removing all images for the provided id
    m_databaseManager.m_pictureDao.removePictureFromAlbum(m_albumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if(albumId <= 0)
    {
        //Create a new, empty album
        m_pictures.reset(new std::vector<std::unique_ptr<Picture>>);
        return;
    }

    //Acquire the list of the pictures, based on the ID
    //This goes through the DB and acquires the needed images
    m_pictures = m_databaseManager.m_pictureDao.picturesFromAlbum(albumId);

}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    if(index.row() < 0 || index.row() >= rowCount() || !index.isValid())
    {
        return false;
    }

    return true;
}
