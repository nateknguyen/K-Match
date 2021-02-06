#include "TrackSort.h"

bool PopularitySort::compare(const Track *t1, const Track *t2) {
    return t1->getPopularity() > t2->getPopularity();
}

bool AlphabeticalSort::compare(const Track *t1, const Track *t2) {
    return t1->getName() < t2->getName();
}