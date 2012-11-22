#ifndef DEF_FORWARDCHECKING
#define DEF_FORMARDCHECKING

#include "Propagator.h"

/* For the moment the forwardChecking class deals only with binary constraints  
    See the definition of Haralick and Elliot HE80 
 
    NON BINARY CONSTRAINTS ARE SKIPPED 

 */

class BinaryForwardChecking : public Propagator {

public:
    BinaryForwardChecking(Problem &problem);

    virtual bool propagate(int variableIndex, int valueIndex, int depth);
    virtual void undoPropagation(int depth);
};

#endif
