#ifndef DEF_DOM
#define DEF_DOM

#include <cassert>

#include "VariableOrderingHeuristic.hh"

class Dom : public VariableOrderingHeuristic
{
public:
  Dom (std::vector <Variable*> const &variables);

  virtual Variable &chooseVariable () const;
};

#endif
