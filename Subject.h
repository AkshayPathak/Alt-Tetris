#ifndef TEST_SUBJECT_H
#define TEST_SUBJECT_H

#include <vector>
#include <memory>
#include "Observer.h"

class Subject {

    std::vector<std::shared_ptr<Observer>> observers;

public:

    Subject();

    void attach(std::shared_ptr<Observer>);

    void detach(std::shared_ptr<Observer>);

    void notifyObserver();

    virtual ~Subject() = 0;

};

#endif //TEST_SUBJECT_H
