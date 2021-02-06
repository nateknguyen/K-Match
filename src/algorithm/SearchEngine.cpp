#include "SearchEngine.h"
#include "../utils/Strings.h"

std::vector<Track*> SearchEngine::search(std::string keyword, const TrackSort& sorter) const {
    keyword = Strings::lower(keyword);
    std::vector<Track*> result;
    for (auto it = om->getTracks()->begin(); it != om->getTracks()->end(); it++) {
        if (Strings::lower(it->second->getName()).find(keyword) != std::string::npos) {
            result.push_back(it->second);
        }
    }

    sorter.sort(result);
    return result;
}