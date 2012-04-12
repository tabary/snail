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

  std::vector <Constraint *> const &getConstraintsCollection() const;

  Variable &getVariable(int variableIndex);
  int getNbVariables();

  int getFirstUnassignedVariable();
  
  void display();

};

#endif
