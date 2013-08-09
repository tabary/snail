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
    unsigned int valueIndex;
    unsigned int depth;
  } variableValue;
  std::stack<variableValue> propagationStack;


public:
  
Propagator (unsigned int nbConstraints);

void dealWith(Constraint *c);

virtual bool propagate (std::vector <Variable*> variablesEvt, unsigned int valueIndex, unsigned int depth) = 0;
virtual void undoPropagation (unsigned int depth) = 0;
  
virtual bool initialize() = 0;
};

#endif
