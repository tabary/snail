#ifndef DEF_FORWARDCHECKING
#define DEF_FORMARDCHECKING


#include "Propagator.h"

class ForwardChecking : public Propagator {


public:
    ForwardChecking(Problem &problem);

    virtual bool propagate(int variableIndex, int valueIndex, int depth);
    virtual void undoPropagation(int depth);
};

#endif
