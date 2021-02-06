#ifndef __KMUTILS_H__
#define __KMUTILS_H__

#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

class Strings {
  public:
    // https://stackoverflow.com/questions/16286095/similar-function-to-javas-string-split-in-c
    static std::vector<std::string> split(const std::string& str, const std::string& separator) {
        char* cstr = const_cast<char*>(str.c_str());
        char* current;
        std::vector<std::string> arr;
        current = strtok(cstr, separator.c_str());
        while (current != NULL) {
            arr.push_back(current);
            current = strtok(NULL, separator.c_str());
        }
        return arr;
    }

    static std::string lower(const std::string str) {
        std::string data = str;
        std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c){ return std::tolower(c); });
        return data;
    }

    static std::string durationFromMs(int ms) {
        int seconds = ms / 1000 % 60;
        int minutes = ms / 60000;
        std::ostringstream temp("");
        temp << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
        return temp.str();
    }
};

#endif