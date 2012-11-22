#ifndef DEF_DOM_THEN_DEG
#define DEF_DOM_THEN_DEG


#include "VariableOrderingHeuristic.h"

class DomThenDeg : public VariableOrderingHeuristic {


public:
    DomThenDeg(std::vector <Variable*> &variables);

    virtual int chooseVariable();
};

#endif
