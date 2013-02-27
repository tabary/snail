#ifndef DEF_PROPAGATOR
#define DEF_PROPAGATOR

#include "stack"
#include "Constraint.h"


class Constraint;


class Propagator
{
private:

protected:

  std::vector <Constraint *> _constraints;
  

  typedef struct
  {
    Variable* variable;
    int valueIndex;
    int depth;
  } variableValue;
  std::stack<variableValue> propagationStack;


public:
  //Propagator (Problem & problem);
Propagator ();

void dealWith(Constraint *c);

  virtual bool propagate (int variableIndex, int valueIndex, int depth) = 0;
  virtual void undoPropagation (int depth) = 0;
};

#endif
