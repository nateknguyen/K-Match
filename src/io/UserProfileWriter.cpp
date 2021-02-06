#include "UserProfileWriter.h"

#include <fstream>

User* UserProfileWriter::importUser(const std::string &id) const {
    std::ifstream inFS(id + ".txt");
    // The user does not exist in a file already
    if (!inFS.is_open()) {
        // Create a new user file and User
        std::ofstream outFS(id + ".txt", std::ofstream::trunc);
        outFS << "Playlist" << std::endl;
        outFS.flush();
        outFS.close();

        return new User(id, "Playlist");
    }

    /*
     * Format of user.txt:
     *  <name of UTL>
     *  <id1>
     *  <id2>
     *  ...
     */

    std::string utlName;
    getline(inFS, utlName);

    User* user = new User(id, utlName);
    std::string songId;
    while (getline(inFS, songId)) {
        // Only add tracks that exist in the ObjectManager
        if (om->getTracks()->find(songId) != om->getTracks()->end()) {
            user->getUTL()->getTrackList()->push_back(songId);
        }
    }

    return user;
}

bool UserProfileWriter::saveUser(const User* user) const {
    std::ofstream outFS(user->getId() + ".txt", std::ofstream::trunc);
    if (!outFS.is_open()) {
        return false;
    }

    outFS << user->getUTL()->getName() << std::endl;
    outFS.flush();

    std::vector<std::string>* trackList = user->getUTL()->getTrackList();
    for (auto it = trackList->begin(); it != trackList->end(); it++) {
        outFS << *it << std::endl;
        outFS.flush();
    }

    outFS.close();
    return true;
}
