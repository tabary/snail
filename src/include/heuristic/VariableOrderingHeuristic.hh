#ifndef DEF_VARIABLE_ORDERING_HEURISTIC
#define DEF_VARIABLE_ORDERING_HEURISTIC

#include <cassert>

#include "global.hh"
#include "Variable.hh"

class VariableOrderingHeuristic
{
private:

protected:
  std::vector <Variable*> const &_variablesCollection;

public:
  VariableOrderingHeuristic (std::vector <Variable*> const &variables);

  virtual Variable &chooseVariable () const = 0;
};

#endif
