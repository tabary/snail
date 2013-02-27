#include "BinaryForwardChecking.h"


using namespace std;

//BinaryForwardChecking::BinaryForwardChecking (Problem &problem) : Propagator (problem)
//{
//assert (problem.getMinArity () == 2 && problem.getMaxArity () == 2);
//}

BinaryForwardChecking::BinaryForwardChecking () : Propagator()
{

}


bool
BinaryForwardChecking::propagate (int variableIndex, int valueIndex, int depth)
{
 
  variableValue v;

  bool check;

  for(int i=0; i < _constraints.size (); ++i){
             
  vector<Variable *> const &scope = _constraints[i]->getScope ();
      tuple &t = _constraints[i]->getMyTuple ();
      int positionOfFutureVariableInScope;

      // Init of the tuple with the assigned variable and determine the index of the second variable (unassigned variable)
      check = false;
      for (int j = 0; j < (int) scope.size (); ++j)
        {
          if (scope[j]->getIndex () == variableIndex){
            t[j] = scope[j]->getDomain ().getValueOfIndex (valueIndex);
            check = true;
            }
          else
            positionOfFutureVariableInScope = j;         
        }

      if (check == false)
        continue;
      
      std::vector<int> const &currentDomainOfFutureVariable = scope[positionOfFutureVariableInScope]->getDomain ().getCurrentDomain ();
      Variable* futureVariable = scope[positionOfFutureVariableInScope];

      for (int j = 0; j < (int) currentDomainOfFutureVariable.size (); ++j)
        {
          if (currentDomainOfFutureVariable[j] == -1)
            {
              t[positionOfFutureVariableInScope] = futureVariable->getDomain ().getValueOfIndex (j);
              if (!_constraints[i]->isValid (t))
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