#ifndef __SEARCH_FUNCTIONALITY__
#define __SEARCH_FUNCTIONALITY__

#include "../handler.hpp"
#include <KMatch.hpp>

#include <iostream>
#include <string>
#include <stdlib.h>

class menuSearch : public handler {
    private:
        handler *nextHandler;
        KMatch* kmatch;
    public:
        menuSearch(KMatch* kmatch) : kmatch(kmatch) { }
        void setNextHandler(handler *request);
        void handleRequest(char c);

        void openTrack(Track* t);
};
#endif