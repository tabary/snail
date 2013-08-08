#include "Propagator.hh"

using namespace std;

Propagator::Propagator (int nbConstraints) 
{
  assert(nbConstraints > 0);
  _recordedConstraints = new bool [nbConstraints];
  memset(_recordedConstraints,false,sizeof(bool) * nbConstraints);
  
}


void 
Propagator::dealWith (Constraint *c)
{
  assert(c != NULL);
_constraints.push_back (c)  ;
_recordedConstraints[c->getIndex ()]=true;
}