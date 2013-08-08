#ifndef DEF_LEXICO
#define DEF_LEXICO

#include <cassert>

#include "VariableOrderingHeuristic.hh"

class Lexico : public VariableOrderingHeuristic
{
public:
  Lexico (std::vector <Variable*> const &variables);

  virtual Variable &chooseVariable () const;
};

#endif
