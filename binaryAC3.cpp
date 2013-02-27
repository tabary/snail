//#include "BinaryAC3.h"
//
//using namespace std;
//
//BinaryAC3::BinaryAC3 (Problem &problem) : Propagator (problem)
//{
//  assert (problem.getMinArity () == 2 && problem.getMaxArity () == 2);
//}
//
//bool
//BinaryAC3::propagate (int variableIndex, int valueIndex, int depth)
//{
//  assert (propagationQueue.empty ());
//
//
//  //  cerr << "Begining of propagation" << endl;
//
//  propagationQueue.push_front (&(_problem.getVariable (variableIndex)));
//  Variable* y;
//
//  while (!propagationQueue.empty ())
//    {
//      Variable& v = *(propagationQueue.front ());
//      propagationQueue.pop_front ();
//
//      //   cerr << "Pick " << v << " in propagation queue" << endl;
//
//
//      vector<Constraint *> const &constraints = v.getInvolvedConstraints ();
//      for (unsigned int i = 0; i < constraints.size (); ++i)
//        {
//
//          //    cerr << "Check " << *(constraints[i]) << endl;
//
//          vector<Variable *> const &scope = constraints[i]->getScope ();
//          for (int j = 0; j < (int) scope.size (); ++j)
//            {
//              if (scope[j]->getIndex () == v.getIndex ())
//                continue;
//              y = scope[j];
//              if (revise (*(constraints[i]), *y, depth))
//                {
//                  if (y->hasEmptyDomain ())
//                    {
//                      propagationQueue.clear ();
//                      return false;
//                    }
//                  propagationQueue.push_back (y);
//                }
//            }
//        }
//    }
//  return true;
//}
//
//bool
//BinaryAC3::revise (Constraint& c, Variable& x, int depth)
//{
//
//  // cerr << "Revise " << x << endl;
//
//
//  int domainSize = x.getDomain ().getNbCurrentValues ();
//  const vector<int>& d = x.getDomain ().getCurrentDomain ();
//  for (unsigned int i = 0; i < d.size (); ++i)
//    if (d[i] == -1 && !seekSupport (c, x, i))
//      {
//        x.getDomain ().removeIndexAtDepth (i, depth);
//        cout << "Removals of  " << i << " at depth " << depth << "for variable " << x.getName () << endl;
//      }
//
//
//  return domainSize != x.getDomain ().getNbCurrentValues ();
//}
//
//
//// TODO
//bool
//BinaryAC3::seekSupport (Constraint& c, Variable& x, int indexValue)
//{
//  return c.seekSupport (x, indexValue);
//}
//
//void
//BinaryAC3::undoPropagation (int depth)
//{
//
//  variableValue v;
//  while (!propagationStack.empty ())
//    {
//      v = propagationStack.top ();
//      if (v.depth < depth)
//        break;
//      propagationStack.pop ();
//#ifdef TRACE  
//      cout << "Undo Propagation at depth " << depth << " of variableIndex :" << v.variableIndex << " with value " << v.valueIndex << endl;
//#endif
//      _problem.getVariable (v.variableIndex).getDomain ().restoreUniqueIndexAtDepth (v.valueIndex, v.depth);
//    }
//
//}