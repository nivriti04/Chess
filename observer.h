#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Board;
// Abstract Observer
class Observer {
 
 public:
 
  virtual void notify(Board& board) = 0;  
  virtual ~Observer() = default;

};
#endif
