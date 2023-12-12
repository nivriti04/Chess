#include "subject.h"

Subject::Subject() {
  observers = std::vector<Observer*>();
}
Subject::~Subject() {}

void Subject::attach(Observer* ob) {
  if(ob != nullptr){
    observers.emplace_back(ob);
  }
  
}

void Subject::detach(Observer* ob) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == ob) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers(Board &board) const {
  for (auto &ob : observers) {
    ob->notify(board);
  }
}
