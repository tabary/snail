#include "Constraint.h"

using namespace std;


Constraint::Constraint(string name, int arity, Variable **scope, Relation const &relation) : d_name(name), d_arity(arity), d_relation(relation)
{
  assert(d_arity >= 1 && scope != NULL);
  d_scope = new Variable*[d_arity];
  memcpy(d_scope,scope,sizeof(scope[0])*d_arity);
} 

bool Constraint::isConsistent()
{
  tuple myTuple= new int[d_arity];
  for(int i=0; i<d_arity; i++){
    if (!d_scope[i]->isAssigned())
      return true;
    myTuple[i] = (d_scope[i]->getDomain()).getUniqueValue(); 
  }
  if (d_relation.isValid(myTuple))
    return true;
  return false;
}


ostream& operator<<(ostream &flux, const Constraint &constraint)
{ 
  flux << constraint.d_name << " [";
  for (int i=0; i< constraint.d_arity; i++){
    flux << constraint.d_scope[i]->getName() << (i<constraint.d_arity-1 ? "," : "" ) ;
  }
  flux << "] with associated relation " << constraint.d_relation ;
  return flux;
}
