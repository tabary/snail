#include "Dom.hh"

using namespace std;

Dom::Dom (vector <Variable*> const &variables) : VariableOrderingHeuristic (variables) { }

Variable &
Dom::chooseVariable () const
{
  int variableIndex = -1;
  for (size_t i(0); i < _variablesCollection.size (); ++i)
    {
      if (_variablesCollection[i]->isAssigned ())
        continue;
      if (variableIndex == -1 || _variablesCollection[i]->getDomain ().getNbCurrentValues () < _variablesCollection[variableIndex]->getDomain ().getNbCurrentValues ())
        variableIndex = i;
    }
  assert (variableIndex != -1);
  return *(_variablesCollection[variableIndex]);
}