#ifndef __TRACKSORT_H__
#define __TRACKSORT_H__

#include "../objects/Track.h"

#include <algorithm>
#include <vector>

class TrackSort {
  public:
    virtual void sort(std::vector<Track*> &vect) const = 0;
};

class PopularitySort : public TrackSort {
  private:
    static bool compare(const Track* t1, const Track* t2);

  public:
    virtual void sort(std::vector<Track*> &vect) const {
        std::sort(vect.begin(), vect.end(), compare);
    }
};

class AlphabeticalSort : public TrackSort {
  private:
    static bool compare(const Track* t1, const Track* t2);

  public:
    virtual void sort(std::vector<Track*> &vect) const {
        std::sort(vect.begin(), vect.end(), compare);
    }
};

#endif