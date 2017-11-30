#include "Subject.h"

Subject::Subject() {}

Subject::~Subject() {
}

void Subject::attach(std::shared_ptr<Observer> observer) {
    observers.emplace_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers() {
    for (const auto &ob : observers) {
        ob->notify();
    }
}
