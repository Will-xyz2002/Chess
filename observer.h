#ifndef OBSERVER_H
#define OBSERVER_H
#include "chessPiece.h"

class Observer {
public:
    virtual void notify(ChessPiece &piece) = 0;
    virtual ~Observer() {}
};
#endif
