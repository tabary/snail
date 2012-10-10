#ifndef DEF_PROPAGATOR
#define DEF_PROPAGATOR

#include "Problem.h"
#include "stack"

class Propagator {
private:

protected:
    
     Problem &_problem; 
     
      typedef struct {
      int variableIndex;
      int valueIndex;
      int depth;
  }variableValue;
  std::stack<variableValue> propagationStack;
     
     
public:
    Propagator(Problem &problem); 
    
    virtual bool propagate(int variableIndex, int valueIndex, int depth) = 0;
    virtual void undoPropagation(int depth) = 0;
};

#endif
