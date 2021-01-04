#include "picture.h"

Picture::Picture(const QUrl &fileUrl) : m_id(-1),
    m_albumId(-1), m_fileUrl(fileUrl)
{

}

Picture::Picture(const QString& filePath) :
    Picture(QUrl::fromLocalFile(filePath))
{

}

Picture::~Picture()
{

}

int Picture::albumId() const
{
    return m_albumId;
}

void Picture::setAlbumId(int albumId)
{
    m_albumId = albumId;
}

int Picture::id() const
{
    return m_id;
}

void Picture::setId(int id)
{
    m_id = id;
}

QUrl Picture::fileUrl() const
{
    return m_fileUrl;
}

void Picture::setFileUrl(const QUrl &fileUrl)
{
    m_fileUrl = fileUrl;
}
