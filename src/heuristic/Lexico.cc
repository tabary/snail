#include "Lexico.hh"

using namespace std;

Lexico::Lexico (vector <Variable*> const &variables) : VariableOrderingHeuristic (variables) { }

Variable &
Lexico::chooseVariable () const
{
  for (size_t i(0); i < _variablesCollection.size (); ++i)
    if (!_variablesCollection[i]->isAssigned ())
      return *(_variablesCollection[i]);
  throw ("Unreachable Code");
}