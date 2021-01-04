#include "albummodel.h"

#include "databasemanager.h"

AlbumModel::AlbumModel(QObject *parent) : QAbstractListModel(parent),
    m_databaseManager(DatabaseManager::instance()),
    m_albums(m_databaseManager.m_albumDao.albums())
{

}

QModelIndex AlbumModel::addAlbum(const Album &album)
{
    //Acquire the current row index
    int rowIndex = rowCount();
    //Start inserting rows, limit just to this one
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<Album> currentAlbum( new Album(album));
    m_databaseManager.m_albumDao.addAlbum(*currentAlbum);
    m_albums->push_back(std::move(currentAlbum));
    //End inserting to this row
    endInsertRows();

    return index(rowIndex, 0);
}

int AlbumModel::rowCount(const QModelIndex &parent) const
{

    Q_UNUSED(parent);

    return m_albums->size();
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const Album& album = *m_albums->at(index.row());

    switch (role)
    {
    case IdRole :
        return album.id();
        break;
    case NameRole:
    case Qt::DisplayRole:
        return album.name();
        break;
    default:
        return QVariant();
    }
}

bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != NameRole)
    {
        return false;
    }

    Album& album = *m_albums->at(index.row());

    album.setName(value.toString());
    m_databaseManager.m_albumDao.updateAlbum(album);

    emit dataChanged(index, index);

    return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent)
{

    if(row < 0 || rowCount() <= row || (row+count) >= rowCount() || count < 0)
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;

    while(countLeft--)
    {
        //Remove each album from the database
        const Album& currentAlbum = *m_albums->at(row+countLeft);
        m_databaseManager.m_albumDao.removeAlbum(currentAlbum.id());
    }

    m_albums->erase(m_albums->begin() + row, m_albums->begin() + row + count);
    endRemoveRows();

    return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Roles::IdRole] = "id";
    roles[Roles::NameRole] = "name";

    return roles ;
}
