#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <vector>
#include <memory>

class QSqlDatabase;
class Album;

using albumContainer = std::unique_ptr<std::vector<std::unique_ptr<Album>>>;

class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database);
    void init() const;
    void addAlbum(Album& album) const;
    void updateAlbum(Album& album) const;
    void removeAlbum(int id) const;
    albumContainer albums() const;
private:
    QSqlDatabase& m_database;

};

#endif // ALBUMDAO_H
