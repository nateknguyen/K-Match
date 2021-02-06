#ifndef __SEARCHENGINE_H__
#define __SEARCHENGINE_H__

#include "TrackSort.h"
#include "../objects/ObjectManager.h"

#include <string>
#include <vector>

class SearchEngine {
  private:
    ObjectManager* om;

  public:
    SearchEngine(ObjectManager* om) : om(om) { }
    std::vector<Track*> search(std::string keyword, const TrackSort& sorter) const;
};

#endif //KMATCH_SEARCHENGINE_H
