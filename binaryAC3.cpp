#include "BinaryAC3.h"

using namespace std;

BinaryAC3::BinaryAC3 (int nbConstraints) : Propagator (nbConstraints)
{
}


bool
BinaryAC3::initialize()
{
  return true;
}

bool // OK
BinaryAC3::propagate (Variable* variable, int valueIndex, int depth)
{
  //assert (propagationQueue.empty ());

  propagationQueue.push_front (variable);  
  Variable* y;

  while (!propagationQueue.empty ())
    {
      Variable& v = *(propagationQueue.front ());
      propagationQueue.pop_front ();

      vector<Constraint *> const &involvedConstraints = v.getInvolvedConstraints ();
      for (unsigned int i = 0; i < involvedConstraints.size (); ++i)
        {
          Constraint& c = *(involvedConstraints[i]);
          vector<Variable *> const &scope = c.getScope ();
          
          for (unsigned int j = 0; j < scope.size (); ++j)
            {
              if (scope[j] == &v)
                continue;
              y = scope[j];
              if (revise (c, *y, depth))
                {
                  if (y->hasEmptyDomain ())
                    {
                      propagationQueue.clear ();
                      return false;
                    }
                  propagationQueue.push_back (y);
                }
            }
        }
    }
  return true;
}

bool // OK
BinaryAC3::revise (Constraint& c, Variable& x, int depth)
{
  variableValue v;
  
  int domainSize = x.getDomain ().getNbCurrentValues ();
  const vector<int>& d = x.getDomain ().getCurrentDomain ();
  for (unsigned int i = 0; i < d.size (); ++i)
    if (d[i] == -1 && !seekSupport (c, x, i)) {
      x.getDomain ().removeIndexAtDepth (i, depth);
      v.variable = &x;
      v.valueIndex = i;
      v.depth = depth;
      propagationStack.push (v);
      }
  return domainSize != x.getDomain ().getNbCurrentValues ();
}

// TODO
bool
BinaryAC3::seekSupport (Constraint& c, Variable& x, int indexValue)
{
  return c.seekSupport (x, indexValue);
}

void
BinaryAC3::undoPropagation (int depth)
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