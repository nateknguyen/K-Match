#ifndef __USER_H__
#define __USER_H__

#include "UserTrackList.h"

#include <string>

class User {
  private:
    const std::string id; // alphanumeric and underscore ONLY
    UserTrackList* utl;

  public:
    User(std::string id, std::string trackListName) : id(id) {
        utl = new UserTrackList(trackListName);
    }

    ~User() {
        delete utl;
    }

    std::string getId() const {
        return id;
    }
    
    UserTrackList* getUTL() const {
        return utl;
    }
};

#endif
