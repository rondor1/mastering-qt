#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <memory>
#include <QHash>

#include "gallery-core_global.h"
#include "picture.h"

class Album;
class AlbumModel;
class DatabaseManager;

class GALLERYCORE_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum PictureRole
    {
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    PictureModel(const AlbumModel& album, QObject* parent = nullptr);

    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    void setAlbumId(int albumId);
    void clearAlbum();

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& m_databaseManager;
    int m_albumId;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> m_pictures;
};

#endif // PICTUREMODEL_H
