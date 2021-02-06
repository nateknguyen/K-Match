#ifndef __USERTRACKLIST_H__
#define __USERTRACKLIST_H__

#include <string>
#include <vector>

class UserTrackList {
  private:
    std::string name;
    std::vector<std::string>* trackList; // contains song Spotify IDs

  public:
    UserTrackList(std::string name) : name(name) {
        trackList = new std::vector<std::string>();
    }

    ~UserTrackList() {
        delete trackList;
    }

    std::string getName() const {
        return name;
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::vector<std::string>* getTrackList() const {
        return trackList;
    }
};

#endif
