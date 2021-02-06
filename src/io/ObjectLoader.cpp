#include "ObjectLoader.h"
#include "../utils/Strings.h"

#include <iostream>
#include <fstream>

bool ObjectLoader::readAlbums() {
    std::ifstream inFS("albums.tsv");
    if (!inFS.is_open()) {
        std::cout << "Unable to open albums.tsv!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFS, line)) {
        std::vector<std::string> split = Strings::split(line, "\t");
        if (split.size() != 3) continue; // Ignore input that does not follow tsv format
        Album* album = new Album(split.at(0), split.at(1), split.at(2));
        om->add(album);
    }

    inFS.close();
    return true;
}

bool ObjectLoader::readArtists() {
    std::ifstream inFS("artists.tsv");
    if (!inFS.is_open()) {
        std::cout << "Unable to open artists.tsv!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFS, line)) {
        std::vector<std::string> split = Strings::split(line, "\t");
        if (split.size() != 2) continue; // Ignore input that does not follow tsv format
        Artist* artist = new Artist(split.at(0), split.at(1));
        om->add(artist);
    }

    inFS.close();
    return true;
}

bool ObjectLoader::readTracks() {
    std::ifstream inFS("tracks.tsv");
    if (!inFS.is_open()) {
        std::cout << "Unable to open tracks.tsv!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFS, line)) {
        std::vector<std::string> split = Strings::split(line, "\t");
        if (split.size() != 5) continue; // Ignore input that does not follow tsv format
        Track* track = new Track(split.at(0), split.at(1), split.at(2), atoi(split.at(3).c_str()), atoi(split.at(4).c_str()));
        om->add(track);
    }

    inFS.close();
    return true;
}

bool ObjectLoader::readAlbumArtists() {
    std::ifstream inFS("album_artists.tsv");
    if (!inFS.is_open()) {
        std::cout << "Unable to open album_artists.tsv!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFS, line)) {
        std::vector<std::string> split = Strings::split(line, "\t");
        if (split.size() != 2) continue; // Ignore input that does not follow tsv format
        om->addAlbumArtist(split.at(0), split.at(1));
    }

    inFS.close();
    return true;
}

bool ObjectLoader::readTrackArtists() {
    std::ifstream inFS("track_artists.tsv");
    if (!inFS.is_open()) {
        std::cout << "Unable to open track_artists.tsv!" << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFS, line)) {
        std::vector<std::string> split = Strings::split(line, "\t");
        if (split.size() != 2) continue; // Ignore input that does not follow tsv format
        om->addTrackArtist(split.at(0), split.at(1));
    }

    inFS.close();
    return true;
}

bool ObjectLoader::loadObjects() {
    return readAlbums() && readArtists() && readTracks() && readAlbumArtists() && readTrackArtists();
}