#include "Lexico.h"

using namespace std;

Lexico::Lexico (vector <Variable*> &variables) : VariableOrderingHeuristic (variables) { }

int
Lexico::chooseVariable ()
{
  for (unsigned int i = 0; i < _variablesCollection.size (); ++i)
    if (!_variablesCollection[i]->isAssigned ())
      return i;
  throw ("Unreachable Code");
}