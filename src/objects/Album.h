#ifndef __ALBUM_H__
#define __ALBUM_H__

#include "KMObject.h"

class Album : public KMObject {
  private:
    const std::string releaseDate;

  public:
    Album(std::string id, std::string name, std::string releaseDate) : KMObject(id, name), releaseDate(releaseDate) { }

    std::string getReleaseDate() const {
        return releaseDate;
    }
};

#endif