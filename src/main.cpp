#include "KMatch.hpp"

#include <iostream>

// Platform checks
#ifdef _WIN32
#include <Windows.h>
#endif

int main() {
    std::cout << "Starting KMatch..." << std::endl;
    KMatch kmatch = KMatch();
    if (kmatch.initialize() != 0) {
        std::cout << "Error initializing KMatch. Please try again." << std::endl;
        return -1;
    }

    // For Windows console
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    return kmatch.mainMenu();
}