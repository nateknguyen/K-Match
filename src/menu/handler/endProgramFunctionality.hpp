#ifndef __END_PROGRAM__
#define __END_PROGRAM__

#include "../handler.hpp"

#include <iostream>
#include <string>
#include <stdlib.h>

class menuEndProgram : public handler {
    private:
        handler *nextHandler;
    public:
        void setNextHandler(handler *request);
        void handleRequest(char c);
};
#endif