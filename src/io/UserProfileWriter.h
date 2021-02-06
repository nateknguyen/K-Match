#ifndef __USERPROFILEWRITER_H__
#define __USERPROFILEWRITER_H__

#include "../objects/ObjectManager.h"
#include "../user/User.h"

class UserProfileWriter {
  private:
    ObjectManager* om;

  public:
    UserProfileWriter(ObjectManager* om) : om(om) { }
    User* importUser(const std::string &id) const;
    bool saveUser(const User* user) const;
};

#endif
