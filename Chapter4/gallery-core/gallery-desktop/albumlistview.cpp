#include "albumlistview.h"
#include "ui_albumlistview.h"

#include <QInputDialog>

#include "albummodel.h"

AlbumListView::AlbumListView(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AlbumListView), m_albumModel(nullptr)
{
    m_ui->setupUi(this);
    connect(m_ui->createAlbumButton, &QAbstractButton::clicked, this, &AlbumListView::createAlbum);
}

AlbumListView::~AlbumListView()
{
    delete m_ui;
}

void AlbumListView::setModel(AlbumModel *model)
{
    m_albumModel = model;
    m_ui->albumList->setModel(m_albumModel);
}

void AlbumListView::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_ui->albumList->setSelectionModel(selectionModel);
}

void AlbumListView::createAlbum()
{
    if(!m_albumModel)
    {
        return;
    }

    bool isOk;
    QString albumName = QInputDialog::getText(this, tr("Album title"),
                                             tr("Type in the name of the album"),
                                             QLineEdit::Normal, "New album",
                                             &isOk);

    if(!albumName.isEmpty() && isOk)
    {
        Album album(albumName);
        QModelIndex index = m_albumModel->addAlbum(album);
        m_ui->albumList->setCurrentIndex(index);
    }
}
