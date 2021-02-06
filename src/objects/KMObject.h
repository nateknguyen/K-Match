#ifndef __KMOBJECT_H__
#define __KMOBJECT_H__

#include <string>

class KMObject {
  protected:
    const std::string id;
    const std::string name;

  public:
    KMObject(std::string id, std::string name) : id(id), name(name) { }

    virtual std::string getId() const {
        return id;
    }

    virtual std::string getName() const {
        return name;
    }
};

#endif