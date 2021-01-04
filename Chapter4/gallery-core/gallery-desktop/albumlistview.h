#ifndef ALBUMLISTVIEW_H
#define ALBUMLISTVIEW_H

#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
class AlbumListView;
}

class AlbumModel;

class AlbumListView : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListView(QWidget *parent = nullptr);
    ~AlbumListView();

    void setModel(AlbumModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void createAlbum();

private:
    Ui::AlbumListView *m_ui;
    AlbumModel* m_albumModel;
};

#endif // ALBUMLISTVIEW_H
