#ifndef DEF_VARIABLE_ORDERING_HEURISTIC
#define DEF_VARIABLE_ORDERING_HEURISTIC

#include "Variable.h"

class VariableOrderingHeuristic
{
private:

protected:
  std::vector <Variable*> &_variablesCollection;

public:
  VariableOrderingHeuristic (std::vector <Variable*> &variables);

  virtual int chooseVariable () = 0;
};

#endif
