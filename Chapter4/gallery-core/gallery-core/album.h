#ifndef ALBUM_H
#define ALBUM_H

#include <QString>

#include "gallery-core_global.h"

class GALLERYCORE_EXPORT Album
{
public:
    explicit Album(const QString& name = "");

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(int id);

private:
    int m_id;
    QString m_name;
};

#endif // ALBUM_H
