#ifndef DEF_PROPAGATOR
#define DEF_PROPAGATOR

#include "stack"
#include <cassert>
#include <string.h>

#include "global.hh"
#include "Constraint.hh"

class Propagator
{
private:

protected:

  std::vector <Constraint *> _constraints;
  bool* _recordedConstraints;

  typedef struct
  {
    Variable* variable;
    int valueIndex;
    int depth;
  } variableValue;
  std::stack<variableValue> propagationStack;


public:
  
Propagator (int nbConstraints);

void dealWith(Constraint *c);

virtual bool propagate (Variable* variable, int valueIndex, int depth) = 0;
virtual void undoPropagation (int depth) = 0;
  
virtual bool initialize() = 0;
};

#endif
