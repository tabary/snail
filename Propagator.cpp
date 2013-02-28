#include "Propagator.h"

using namespace std;

Propagator::Propagator (int nbConstraints) 
{
  _recordedConstraints = new bool [nbConstraints];
  memset(_recordedConstraints,false,sizeof(bool) * nbConstraints);
  
}


void 
Propagator::dealWith (Constraint *c)
{
_constraints.push_back (c)  ;
_recordedConstraints[c->getIndex ()]=true;
}