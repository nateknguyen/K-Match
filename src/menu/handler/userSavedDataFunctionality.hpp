#ifndef __SAVED_DATA_FUNCTIONALITY__
#define __SAVED_DATA_FUNCTIONALITY__

#include "../handler.hpp"
#include <KMatch.hpp>

#include <iostream>
#include <string>
#include <stdlib.h>

class menuSavedData : public handler {
    private:
        KMatch* kmatch;
        handler *nextHandler;
    public:
        menuSavedData(KMatch* kmatch) : kmatch(kmatch) { }
        void setNextHandler(handler *request);
        void handleRequest(char c);
        void openTrack(Track* t);
};
#endif