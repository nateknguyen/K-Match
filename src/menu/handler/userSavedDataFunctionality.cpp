#include "userSavedDataFunctionality.hpp"
#include "../handler.hpp"
#include <utils/Strings.h>

void menuSavedData::setNextHandler(handler *request){
    nextHandler = request;
}

void menuSavedData::handleRequest(char c){
    char input = c;
    std::string response = "";
    if(input == '2'){
        while(response!="0")
        {
            std::cout << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "Saved Songs: " << std::endl;

            std::vector<std::string>* songs = kmatch->getUser()->getUTL()->getTrackList();
            int num = 1;
            if (!songs->empty()) {
                for (auto it = songs->begin(); it != songs->end(); it++) {
                    Track *t = kmatch->getObjectManager()->getTrack(*it);
                    std::cout << "[" << num << "] " << t->getName() << " - ";
                    auto artistVect = kmatch->getObjectManager()->getTrackArtists(t->getId());
                    auto aIt = artistVect.begin();
                    while (aIt != artistVect.end()) {
                        std::cout << kmatch->getObjectManager()->getArtist(*aIt)->getName();
                        aIt++;
                        if (aIt != artistVect.end()) {
                            std::cout << ", ";
                        } else {
                            std::cout << std::endl;
                        }
                    }
                    num++;
                }
            } else {
                std::cout << "You have no saved songs!" << std::endl;
            }

            std::cout << "Type the number corresponding to the song choice or '0' to exit." << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
            getline(std::cin, response);
            if (response != "0") {
                if (is_number(response)) {
                    int num = atoi(response.c_str());
                    if (num - 1 < songs->size()) {
                        openTrack(kmatch->getObjectManager()->getTrack(songs->at(num - 1)));
                    } else {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                } else {
                    std::cout << "Invalid input. Please try again" << std::endl;
                }
            }
        }
    }
    else if (input != NULL){
        nextHandler->handleRequest(input);
    }
}

void menuSavedData::openTrack(Track* t) {
    std::cout << "Track information for " << t->getName() << ":" << std::endl;
    std::cout << "Artists: ";
    auto artistVect = kmatch->getObjectManager()->getTrackArtists(t->getId());
    auto aIt = artistVect.begin();
    while (aIt != artistVect.end()) {
        std::cout << kmatch->getObjectManager()->getArtist(*aIt)->getName();
        aIt++;
        if (aIt != artistVect.end()) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }
    Album* album = kmatch->getObjectManager()->getAlbum(t->getAlbumId());
    std::cout << "Album: " << album->getName() << " (Released: " << album->getReleaseDate() << ")" << std::endl;
    std::cout << "Duration: " << Strings::durationFromMs(t->getDurationMs()) << std::endl;
    std::cout << "Listen at: https://open.spotify.com/embed?uri=spotify:track:" << t->getId() << std::endl;

    std::string response;
    std::cout << "Enter [0] to go back." << std::endl;
    getline(std::cin, response);
    if (response == "0") {
        return;
    } else {
        std::cout << "Invalid input. Please try again." << std::endl;
        openTrack(t);
    }
}