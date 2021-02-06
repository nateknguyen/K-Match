#ifndef __OBJECTLOADER_H__
#define __OBJECTLOADER_H__

#include "../objects/ObjectManager.h"

class ObjectLoader {
  private:
    ObjectManager* om;
    bool readAlbums();
    bool readArtists();
    bool readTracks();
    bool readAlbumArtists();
    bool readTrackArtists();

  public:
    ObjectLoader(ObjectManager* om) : om(om) { }
    bool loadObjects();
};

#endif