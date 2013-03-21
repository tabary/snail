#ifndef DEF_DOM_ON_DEG
#define DEF_DOM_ON_DEG


#include "VariableOrderingHeuristic.h"

class DomOnDeg : public VariableOrderingHeuristic
{
public:
  DomOnDeg (std::vector <Variable*> &variables);

  virtual int chooseVariable ();
};

#endif
