#include "albumwidget.h"
#include "ui_albumwidget.h"

#include <QModelIndex>
#include <QInputDialog>
#include <QFileDialog>

#include "albummodel.h"
#include "thumbnailproxymodel.h"
#include <picturemodel.h>

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AlbumWidget),
    m_albumModel(nullptr),
    m_albumSelectionModel(nullptr),
    m_pictureModel(nullptr),
    m_pictureSelectionModel(nullptr)
{
    m_ui->setupUi(this);

    m_ui->thumbnailListView->setSpacing(5);
    m_ui->thumbnailListView->setResizeMode(QListView::Adjust);
    m_ui->thumbnailListView->setFlow(QListView::LeftToRight);
    m_ui->thumbnailListView->setWrapping(true);

    connect(m_ui->addPicturesButton, &QPushButton::clicked, this, &AlbumWidget::addPictures);
    connect(m_ui->deleteButton, &QPushButton::clicked, this, &AlbumWidget::deleteAlbum);
    connect(m_ui->editButton, &QPushButton::clicked, this, &AlbumWidget::editAlbum);
}

AlbumWidget::~AlbumWidget()
{
    delete m_ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel)
{
    m_albumModel = albumModel;

    connect(m_albumModel, &QAbstractItemModel::dataChanged,
            [this](const QModelIndex& topLeft)->void{
        if(topLeft == m_albumSelectionModel->currentIndex())
        {
            loadAlbum(topLeft);
        }
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel *selectionModel)
{
    m_albumSelectionModel = selectionModel;

    connect(m_albumSelectionModel, &QItemSelectionModel::selectionChanged,
            [this](const QItemSelection& selected)->void{
        if(selected.isEmpty())
        {
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first());
    });
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel *thumbnailProxyModel)
{
    m_pictureModel = thumbnailProxyModel;
    m_ui->thumbnailListView->setModel(m_pictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel *pictureSelectionModel)
{
    m_pictureSelectionModel = pictureSelectionModel;
    m_ui->thumbnailListView->setSelectionModel(m_pictureSelectionModel);
}

void AlbumWidget::clearUi()
{
    m_ui->albumName->setText("");
    m_ui->deleteButton->setVisible(false);
    m_ui->editButton->setVisible(false);
    m_ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex &albumIndex)
{

}

void AlbumWidget::deleteAlbum()
{
    if(m_albumSelectionModel->selectedIndexes().isEmpty())
    {
        return;
    }

    auto row = m_albumSelectionModel->currentIndex().row();
    m_albumModel->removeRow(row);

    QModelIndex previousModelIndex = m_albumModel->index(row - 1, 0);
    if(previousModelIndex.isValid())
    {
        m_albumSelectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }

    QModelIndex nextModelIndex = m_albumModel->index(row, 0);
    if(previousModelIndex.isValid())
    {
        m_albumSelectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }
}

void AlbumWidget::editAlbum()
{
    if(m_albumSelectionModel->selectedIndexes().isEmpty())
    {
        return;
    }

    QModelIndex currentIndex = m_albumSelectionModel->selectedIndexes().first();
    QString albumName = m_albumModel->data(currentIndex, AlbumModel::Roles::NameRole).toString();
    bool isNameOk;

    QString newName = QInputDialog::getText(this, tr("Edit album name"), tr("New album name"), QLineEdit::Normal, albumName, &isNameOk);

    if(isNameOk && !newName.isEmpty())
    {
        m_albumModel->setData(currentIndex, newName, AlbumModel::Roles::NameRole);
    }

}

void AlbumWidget::addPictures()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Add pictures"),
                                                          QDir::homePath(),
                                                          tr("Picture files (*.jpg *.png)"));

    if(!fileNames.isEmpty())
    {
        QModelIndex lastIndex;
        for(auto fileName : fileNames)
        {
            Picture picture(fileName);
            lastIndex = m_pictureModel->pictureModel()->addPicture(picture);
        }
        m_ui->thumbnailListView->setCurrentIndex(lastIndex);
    }
}
