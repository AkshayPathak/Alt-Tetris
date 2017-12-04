#ifndef QUADRIS_OBSERVER_H
#define QUADRIS_OBSERVER_H

class Observer {

public:
    virtual void notify() = 0;

    virtual ~Observer();
};

#endif //QUADRIS_OBSERVER_H
