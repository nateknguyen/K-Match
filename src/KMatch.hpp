#ifndef __KMATCH_H__
#define __KMATCH_H__

#include "algorithm/SearchEngine.h"
#include "io/ObjectLoader.h"
#include "user/User.h"

class KMatch {
  private:
    User* user;
    ObjectManager* om;
    SearchEngine* se;

  public:
    int initialize();
    int mainMenu();

    ObjectManager* getObjectManager() {
        return om;
    }

    SearchEngine* getSearchEngine() {
        return se;
    }

    User* getUser() {
        return user;
    }
};

#endif