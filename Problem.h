#ifndef DEF_PROBLEM
#define DEF_PROBLEM

#include "Variable.h"
#include "Constraint.h"




class Problem
{
private:
  std::string _name;
  std::vector <Variable*> _variablesCollection;
  std::vector <Constraint *> _constraintsCollection;

  int minArity;
  int maxArity;

public:
  Problem ();

  void setName (const std::string &name);

  void addVariable (Variable *variable);
  void addConstraint (Constraint *constraint);

  std::vector <Constraint *> const &getConstraintsCollection () const;
  std::vector <Variable *> &getVariablesCollection ();

  Variable &getVariable (int variableIndex) const;
    
  int getNbVariables () const;
  int getNbConstraints () const;

  int getMinArity ();
  int getMaxArity ();

  void display () const;
};

#endif
