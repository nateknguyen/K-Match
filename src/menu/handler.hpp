#ifndef __HANDLER_HPP_
#define __HANDLER_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <stdlib.h>

class handler {
    private:
        handler *nextRequest;
    protected:
        bool is_number(const std::string& s){
            return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
        }
    public: 
        handler(){
            nextRequest = NULL;
        }
        ~handler(){ };
        virtual void setNextHandler(handler *nextHandler) = 0;
        virtual void handleRequest(char c) = 0;
};


#endif