#ifndef DEF_LEXICO
#define DEF_LEXICO

#include <cassert>

#include "VariableOrderingHeuristic.h"

class Lexico : public VariableOrderingHeuristic
{
public:
  Lexico (std::vector <Variable*> &variables);

  virtual int chooseVariable ();
};

#endif
