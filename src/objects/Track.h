#ifndef __TRACK_H__
#define __TRACK_H__

#include "KMObject.h"

class Track : public KMObject {
  private:
    const std::string albumId;
    const int durationMs;
    const int popularity;
    
  public:
    Track(std::string id, std::string name, std::string albumId, int durationMs, int popularity) : KMObject(id, name), albumId(albumId), durationMs(durationMs), popularity(popularity) { }

    std::string getAlbumId() const {
        return albumId;
    }

    int getDurationMs() const {
        return durationMs;
    }

    int getPopularity() const {
        return popularity;
    }
};

#endif