PROJECT(KMatch)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILES src/main.cpp
        src/KMatch.cpp
        src/algorithm/SearchEngine.cpp
        src/algorithm/TrackSort.cpp
        src/io/ObjectLoader.cpp
        src/io/UserProfileWriter.cpp
        src/menu/handler/endProgramFunctionality.cpp
        src/menu/handler/searchFunctionality.cpp
        src/menu/handler/userSavedDataFunctionality.cpp
        src/objects/ObjectManager.cpp)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(kmatch ${SOURCE_FILES})
