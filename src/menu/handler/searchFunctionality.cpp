#include "searchFunctionality.hpp"
#include "../handler.hpp"
#include <utils/Strings.h>

#include <algorithm>

void menuSearch::setNextHandler(handler *request){
    nextHandler = request;
}

void menuSearch::handleRequest(char c){
    bool searched = false;
    int page = 1;
    int maxPages = 0;
    std::vector<Track*> results;

    char input = c;
    std::string response = "";         
    if (input == '1') {
        while (response != "0") {
            std::cout << std::endl;
            if (!searched) {
                page = 1;
                std::cout << "---------------------------------------------------------------" << std::endl;
                std::cout << "   Please enter in the song you are searching for " << std::endl;
                std::cout << "   or enter 0 to return to the main menu." << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;

                getline(std::cin, response);
                TrackSort* sorter = new PopularitySort(); // Change the sort here
                results = kmatch->getSearchEngine()->search(response, *sorter);
                searched = true;
            } else {
                std::string searchResponse;
                int num = (page - 1) * 9 + 1;
                maxPages = results.size() / 9 + (std::min((int) results.size() % 9, 1));
                int resultsShown = 0;
                std::cout << "Found " << results.size() << " songs to browse. (Page " << page << "/" << maxPages << ")" << std::endl;
                for (auto it = results.begin() + num - 1; it != results.end() && resultsShown < 9; it++) {
                    Track* t = *it;
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
                    resultsShown++;
                }

                std::cout << std::endl << "Enter the number for the song you would like to view." << std::endl;
                std::cout << "To go to the next page, enter 'N'. To go to the previous page, enter 'P'." << std::endl;
                std::cout << "If you would like to search again, enter 0." << std::endl;
                getline(std::cin, searchResponse);

                if (searchResponse == "n" || searchResponse == "N") {
                    if (page + 1 <= maxPages) {
                        page++;
                    } else {
                        std::cout << "Cannot increase pages anymore!" << std::endl;
                    }
                } else if (searchResponse == "p" || searchResponse == "P") {
                    if (page > 1) {
                        page--;
                    } else {
                        std::cout << "Cannot decrease pages anymore!" << std::endl;
                    }
                } else if (searchResponse == "0") {
                    searched = false;
                } else if (is_number(searchResponse)) {
                    int num = atoi(searchResponse.c_str());
                    if (num - 1 < results.size()) {
                        openTrack(results.at(num - 1));
                    } else {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                } else{
                    std::cout << "Invalid input. Please try again." << std::endl;
                }
            }
        }
    }
    else if (input == '0'){
        return;
    }
    else if (input != NULL){
        nextHandler->handleRequest(input);
    }
}

void menuSearch::openTrack(Track* t) {
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
    std::cout << "Enter [0] to go back, [1] to save this song to your saved songs" << std::endl;
    getline(std::cin, response);
    if (response == "0") {
        return;
    } else if (response == "1") {
        std::vector<std::string>* trackList = kmatch->getUser()->getUTL()->getTrackList();
        if (std::find(trackList->begin(), trackList->end(), t->getId()) != trackList->end()) {
            std::cout << t->getName() << " is already in your saved songs!" << std::endl;
        } else {
            trackList->push_back(t->getId());
            std::cout << "Added " << t->getName() << " to your saved songs!" << std::endl;
        }
    } else {
        std::cout << "Invalid input. Please try again." << std::endl;
        openTrack(t);
    }
}