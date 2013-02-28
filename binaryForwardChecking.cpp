#include "BinaryForwardChecking.h"


using namespace std;

BinaryForwardChecking::BinaryForwardChecking (int nbConstraints) : Propagator (nbConstraints) { }

bool
BinaryForwardChecking::propagate (Variable* variable, int valueIndex, int depth)
{
  variableValue v;

  vector <Constraint *> const & involvedConstraints = variable->getInvolvedConstraints ();
  for (int i = 0; i < (int) involvedConstraints.size (); ++i)
    {
      Constraint & c = *(involvedConstraints[i]);
      if (!_recordedConstraints[c.getIndex ()] )
        continue;
          
      vector<Variable *> const &scope = c.getScope ();
      int positionOfFutureVariableInScope;
      tuple &t = c.getMyTuple ();

      // Init of the tuple with the assigned variable and determine the index of the second variable (unassigned variable)
      if (scope[0]== variable)
        {
          t[0] = variable->getDomain ().getValueOfIndex (valueIndex);
          positionOfFutureVariableInScope = 1;
        }
      else 
        {
          t[1] = variable->getDomain ().getValueOfIndex (valueIndex);
          positionOfFutureVariableInScope = 0;
        }
      
      vector<int> const &currentDomainOfFutureVariable = scope[positionOfFutureVariableInScope]->getDomain ().getCurrentDomain ();
      Variable* futureVariable = scope[positionOfFutureVariableInScope];

      for (int j = 0; j < (int) currentDomainOfFutureVariable.size (); ++j)
        {
          if (currentDomainOfFutureVariable[j] == -1)
            {
              t[positionOfFutureVariableInScope] = futureVariable->getDomain ().getValueOfIndex (j);
              if (!c.isValid (t))
                {
                  v.variable = futureVariable;
                  v.valueIndex = j;
                  v.depth = depth;
                  propagationStack.push (v);
                  futureVariable->getDomain ().removeIndexAtDepth (j, depth);
#ifdef TRACE  
                  cout << "Propagation at depth " << v.depth << " of variable :" << v.variable->getName () << " with valueIndex " << v.valueIndex << endl;
#endif
                }
            }
        }

      if (futureVariable->hasEmptyDomain ())
        return false;
    }
  return true;
}

void
BinaryForwardChecking::undoPropagation (int depth)
{
  variableValue v;
  while (!propagationStack.empty ())
    {
      v = propagationStack.top ();
      if (v.depth < depth)
        break;
      propagationStack.pop ();
#ifdef TRACE  
      cout << "Undo Propagation at depth " << depth << " of variable :" << v.variable->getName () << " with value " << v.valueIndex << endl;
#endif
      v.variable->getDomain ().restoreUniqueIndexAtDepth (v.valueIndex, v.depth);
    }

}