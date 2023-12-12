#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include "observer.h"
#include <vector> 
#include <memory>

class Board;

class Subject {
    
    protected: 
        std::vector<Observer*> observers;    
    public: 
        void attach(Observer* ob);  // Attaching an observer to the subject 
        void detach(Observer* ob); // remove from observer

        void notifyObservers(Board &board) const; // Notify all observers to make the switch ?? 

        // Dtor 
        virtual ~Subject() = 0;
        Subject();
}; 

#endif 
