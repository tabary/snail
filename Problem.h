#ifndef DEF_PROBLEM
#define DEF_PROBLEM

#include "Variable.h"
#include "Constraint.h"

class Problem
{
 private :
  std::vector <Variable*> d_variablesCollection;
  std::vector <Constraint *> d_constraintsCollection;

 public :
  Problem();
 
  void addVariable(Variable *variable);
  void addConstraint(Constraint *constraint);

  Variable &getVariable(int variableIndex);

  int getFirstUnassignedVariable();

  void display();

};

#endif
