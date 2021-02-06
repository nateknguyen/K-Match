#ifndef __ARTIST_H__
#define __ARTIST_H__

#include "KMObject.h"

class Artist : public KMObject {
  public:
    Artist(std::string id, std::string name) : KMObject(id, name) { }
};

#endif