#include "BinaryAC3.hh"

using namespace std;

BinaryAC3::BinaryAC3 (unsigned int nbConstraints) : Propagator (nbConstraints) { }

bool
BinaryAC3::initialize ()
{
  return true;
}

bool
BinaryAC3::propagate (Variable* variable, unsigned int valueIndex, unsigned int depth)
{
  assert (propagationQueue.empty ());


  //     
  //     seekSupport(*(involvedConstraints[0]),*variable,valueIndex);

  propagationQueue.push_front (variable);

  while (!propagationQueue.empty ())
    {
      Variable& v = *(propagationQueue.front ());
      propagationQueue.pop_front ();

      vector<Constraint *> const &involvedConstraints = v.getInvolvedConstraints ();
      for (size_t i (0); i < involvedConstraints.size (); ++i)
        {
          Constraint& c = *(involvedConstraints[i]);
          if (!_recordedConstraints[c.getIndex ()])
            continue;
          vector<Variable *> const &scope = c.getScope ();

          for (size_t j (0); j < scope.size (); ++j)
            {
              if (scope[j] == &v)
                continue;
              Variable& y = *(scope[j]);
              if (revise (c, y, depth))
                {
                  if (y.hasEmptyDomain ())
                    {
#ifdef TRACE  
                      cout << "AC3 Propagation,  " << y.getName () << " has an empty domain" << endl;
#endif

                      propagationQueue.clear ();
                      return false;
                    }
                  auto isAlreadyPresent = std::find(propagationQueue.begin(), propagationQueue.end(), &y);
                  if (isAlreadyPresent == propagationQueue.end ()) propagationQueue.push_back (&y);
                }
            }
        }
    }
  return true;
}

void
BinaryAC3::printTuple (const snail::tuple &t, int arity)
{
  cout << "tuple t = [";
  for (int i = 0; i < arity; ++i)
    cout << t[i] << (i + 1 == arity ? "" : ",");
  cout << "]" << endl;
}

bool
BinaryAC3::revise (Constraint& c, Variable& x, unsigned int depth)
{
  variableValue v;
  
  unsigned int domainSize = x.getDomain ().getNbCurrentValues ();
  const vector<int>& d = x.getDomain ().getCurrentDomain ();
  for (size_t i (0); i < d.size (); ++i)
    if (d[i] == -1 && !seekSupport (c, x, i))
      {
#ifdef TRACE  
        cout << "AC3 Propagation, removals of  " << x.getName () << " = " << x.getDomain ().getValueOfIndex (i) << " at depth " << depth << endl;
#endif
        x.getDomain ().removeIndexAtDepth (i, depth);
        v.variable = &x;
        v.valueIndex = i;
        v.depth = depth;
        propagationStack.push (v);
      }
  return domainSize != x.getDomain ().getNbCurrentValues ();
}


bool
BinaryAC3::seekSupport (Constraint& c, Variable& x, unsigned int indexValue)
{

  const snail::tuple &tupleIndex = c.getMyTupleIndex ();
  const snail::tuple &tupleValue = c.getMyTupleValue ();
  unsigned int arity = c.getArity ();
  vector<Variable *> const &scope = c.getScope ();


  for (size_t i (0); i < scope.size (); ++i)
    if (scope[i] == &x)
      {
        tupleIndex[i] = indexValue;
        tupleValue[i] = x.getDomain ().getValueOfIndex (tupleIndex[i]);
      }
    else
      {
        tupleIndex[i] = scope[i]->getDomain ().getFirstPresentIndex ();
        tupleValue[i] = scope[i]->getDomain ().getValueOfIndex (tupleIndex[i]);
      }

 unsigned int cpt (arity - 1);

  int index;

  do
    {

      //printTuple(tupleValue,arity);
      if (c.isValid (tupleValue))
        return true;
      index = (scope[cpt] == &x ? -1 : scope[cpt]->getDomain ().getNextPresentIndexAfter (tupleIndex[cpt]));

      if (index == -1)
        {
          do
            {
              --cpt;
              if (scope[cpt] == &x)
                {
                  if (cpt == 0)
                    {
                      break;
                    }
                  else
                    {
                      continue;
                    }
                }
              index = scope[cpt]->getDomain ().getNextPresentIndexAfter (tupleIndex[cpt]);
            }
          while (index == -1 && cpt != 0);

          if (index == -1 && cpt == 0)
            break;
          if (index != -1)
            {
              tupleIndex[cpt] = index;
              tupleValue[cpt] = scope[cpt]->getDomain ().getValueOfIndex (tupleIndex[cpt]);
              for (unsigned int i (cpt + 1); i < arity; ++i)
                if (scope[i] != &x)
                  {
                    tupleIndex[i] = scope[i]->getDomain ().getFirstPresentIndex ();
                    tupleValue[i] = scope[i]->getDomain ().getValueOfIndex (tupleIndex[i]);
                  }
              cpt = arity - 1;
            }

        }
      else
        {
          tupleIndex[cpt] = index;
          tupleValue[cpt] = scope[cpt]->getDomain ().getValueOfIndex (tupleIndex[cpt]);
        }

    }
  while (true);



  return false;
}

void
BinaryAC3::undoPropagation (unsigned int depth)
{

   variableValue v;
  while (!propagationStack.empty ())
    {
      v = propagationStack.top ();
      if (v.depth < depth)
        return ;
     propagationStack.pop ();
#ifdef TRACE  
      cout << "Undo Propagation at depth " << depth << " of variable :" << v.variable->getName () << " with value " << v.variable->getDomain ().getValueOfIndex (v.valueIndex) << endl;
#endif
      v.variable->getDomain ().restoreUniqueIndexAtDepth (v.valueIndex, v.depth);
    }

}