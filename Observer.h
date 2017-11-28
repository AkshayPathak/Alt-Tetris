#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

class Observer {

public:
    virtual void notify() = 0;

    virtual ~Observer();
};

#endif //TEST_OBSERVER_H
