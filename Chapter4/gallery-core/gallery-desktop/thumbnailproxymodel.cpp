#include "thumbnailproxymodel.h"

#include "picturemodel.h"
#include "databasemanager.h"
#include <QVariant>


const unsigned int THUMBNAIL_SIZE = 350u;

ThumbnailProxyModel::ThumbnailProxyModel(QObject *parent) : QIdentityProxyModel(parent), m_thumbnails()
{

}

QVariant ThumbnailProxyModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DecorationRole)
    {
        //Generic call, if the role is not corresponding
        return QIdentityProxyModel::data(index, role);
    }

    //Data role is valid, acquire the needed key
    QString dataPath = sourceModel()->data(index, PictureModel::FilePathRole).toString();

    return *m_thumbnails[dataPath];
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if(!sourceModel)
    {
        return;
    }

    connect(sourceModel, &QAbstractItemModel::modelReset,
            [this]{reloadThumbnails();});

    connect(sourceModel, &QAbstractItemModel::rowsInserted,
            [this](const QModelIndex& parent, int first, int last)
    {
        Q_UNUSED(parent);
        generateThumbnails(index(first, 0), last - first + 1);
    });

}

PictureModel *ThumbnailProxyModel::pictureModel() const
{
    return static_cast<PictureModel*>(sourceModel());
}

void ThumbnailProxyModel::generateThumbnails(const QModelIndex &startIndex, int count)
{
    if(!startIndex.isValid())
    {
        return;
    }

    const QAbstractItemModel* model = startIndex.model();
    int lastItem = startIndex.row() + count;
    for(int i = startIndex.row(); i < lastItem; ++i)
    {
        //Take the name of the file
        QString filepath = model->data(model->index(i, 0), PictureModel::FilePathRole).toString();
        QPixmap pixmap(filepath);
        auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE, THUMBNAIL_SIZE,
                                                   Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_thumbnails.insert(filepath, thumbnail);
    }

}

void ThumbnailProxyModel::reloadThumbnails()
{
    qDeleteAll(m_thumbnails);
    m_thumbnails.clear();
    generateThumbnails(index(0,0), rowCount());
}
