#include "Propagator.h"

using namespace std;

Propagator::Propagator () 
{
}


void 
Propagator::dealWith (Constraint *c)
{
_constraints.push_back (c)  ;
}