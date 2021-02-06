#include "endProgramFunctionality.hpp"

void menuEndProgram::setNextHandler(handler *request){
    nextHandler = request;
}

void menuEndProgram::handleRequest(char c){
    char input = c;
    if (input == '0'){
        std::cout << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "                       Ending program" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
    }
    else if (input != NULL){
        std::cout << "Please enter a valid option" << std::endl;
    }
}