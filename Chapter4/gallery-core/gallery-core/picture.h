#ifndef PICTURE_H
#define PICTURE_H

#include "gallery-core_global.h"

#include <QUrl>
#include <QString>

class GALLERYCORE_EXPORT Picture
{
public:
    Picture(const QUrl& fileUrl);
    Picture(const QString& filePath = "");
    ~Picture();

    int albumId() const;
    void setAlbumId(int albumId);

    int id() const;
    void setId(int id);

    QUrl fileUrl() const;
    void setFileUrl(const QUrl &fileUrl);

private:
    int m_id;
    int m_albumId;
    QUrl m_fileUrl;
};

#endif // PICTURE_H
