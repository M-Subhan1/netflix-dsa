#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include "SinglyLinkedList.hpp"

struct Actor {
    std::string *name;

    Actor(const char *name) {
        this->name->assign(name);
    }

    ~Actor() {
        if (name) delete name;
    }
};

#endif