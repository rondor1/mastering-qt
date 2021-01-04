#ifndef PICTUREDAO_H
#define PICTUREDAO_H

class QSqlDatabase;
class Picture;
#include <memory>
#include <vector>

using pictureContainer = std::unique_ptr<std::vector<std::unique_ptr<Picture>>>;

class PictureDao
{
public:
    PictureDao(QSqlDatabase& database);
    void init() const;
    void addPictureInAlbum(int albumId, Picture& picture) const;
    void removePicture(int id) const;
    void removePictureFromAlbum(int albumId);

    pictureContainer picturesFromAlbum(int albumId) const;

private:
    QSqlDatabase& m_database;
};

#endif // PICTUREDAO_H
