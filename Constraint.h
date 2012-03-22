#ifndef DEF_CONSTRAINT
#define DEF_CONSTRAINT

#include "Relation.h"
#include "Variable.h"

class Constraint
{
 private :
  std::string d_name;
  int d_arity;
  Variable **d_scope;
  Relation const &d_relation;

 public :
  Constraint(std::string name, int arity, Variable **scope, Relation const &relation); // The associated domain must be previously created
  
  friend std::ostream& operator<<(std::ostream &flux, const Constraint &constraint);
};

#endif
