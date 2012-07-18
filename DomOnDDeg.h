#ifndef DEF_DOM_ON_DDEG
#define DEF_DOM_ON_DDEG


#include "VariableOrderingHeuristic.h"

class DomOnDDeg : public VariableOrderingHeuristic {


public:
    DomOnDDeg(std::vector <Variable*> &variables);

    virtual int selectVariable();
};

#endif
