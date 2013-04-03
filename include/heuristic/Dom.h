#ifndef DEF_DOM
#define DEF_DOM

#include <cassert>

#include "VariableOrderingHeuristic.h"

class Dom : public VariableOrderingHeuristic
{
public:
  Dom (std::vector <Variable*> &variables);

  virtual int chooseVariable ();
};

#endif
