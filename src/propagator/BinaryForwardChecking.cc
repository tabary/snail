#include "BinaryForwardChecking.hh"


using namespace std;

BinaryForwardChecking::BinaryForwardChecking (unsigned int nbConstraints) : Propagator (nbConstraints) 
{
}

bool
BinaryForwardChecking::initialize()
{
  return true;
}

bool
BinaryForwardChecking::propagate (Variable* variable, unsigned int valueIndex, unsigned int depth)
{
  variableValue v;

  vector <Constraint *> const & involvedConstraints = variable->getInvolvedConstraints ();
  for (size_t i(0); i < involvedConstraints.size (); ++i)
    {
      Constraint & c = *(involvedConstraints[i]);
      if (!_recordedConstraints[c.getIndex ()] )
        continue;
 
      assert(c.getArity () == 2);
      
      vector<Variable *> const &scope = c.getScope ();
      int positionOfFutureVariableInScope;
      const snail::tuple &t = c.getMyTupleValue ();

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

      for (size_t j(0); j < currentDomainOfFutureVariable.size (); ++j)
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
                  cout << "Propagation at depth " << v.depth << " of  :" << v.variable->getName () << " != " << v.variable->getDomain ().getValueOfIndex (v.valueIndex) << endl;
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
BinaryForwardChecking::undoPropagation (unsigned int depth)
{
  variableValue v;
  while (!propagationStack.empty ())
    {
      v = propagationStack.top ();
      if (v.depth < depth)
        return;
      propagationStack.pop ();
#ifdef TRACE  
      cout << "Undo Propagation at depth " << depth << " of variable :" << v.variable->getName () << " with value " << v.variable->getDomain ().getValueOfIndex (v.valueIndex) << endl;
#endif
      v.variable->getDomain ().restoreUniqueIndexAtDepth (v.valueIndex, v.depth);
    }

}
