#include "thumbnailproxymodel.h"

#include "picturemodel.h"
#include <QVariant>

const unsigned int THUMBNAIL_SIZE = 350u;

ThumbnailProxyModel::ThumbnailProxyModel(QObject *parent)
{

}

QVariant ThumbnailProxyModel::data(const QModelIndex &index, int role) const
{

}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{

}

PictureModel *ThumbnailProxyModel::pictureModel() const
{

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
    }

}

void ThumbnailProxyModel::reloadThumbnails()
{

}
