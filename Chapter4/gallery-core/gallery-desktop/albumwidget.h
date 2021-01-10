#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>

namespace Ui {
class AlbumWidget;
}

class AlbumModel;
class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* selectionModel);
    void setPictureModel(ThumbnailProxyModel* thumbnailProxyModel);
    void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

private:
    void clearUi();
    void loadAlbum(const QModelIndex& albumIndex);

signals:
    void pictureActivated(const QModelIndex& index);

private slots:
    void deleteAlbum();
    void editAlbum();
    void addPictures();

private:
    Ui::AlbumWidget *m_ui;
    AlbumModel* m_albumModel;
    QItemSelectionModel* m_albumSelectionModel;

    ThumbnailProxyModel* m_pictureModel;
    QItemSelectionModel* m_pictureSelectionModel;
};

#endif // ALBUMWIDGET_H
