#ifndef DEF_PROBLEM
#define DEF_PROBLEM

#include "Variable.hh"
#include "Constraint.hh"

#include <unordered_map>
#include <cassert>



class Problem
{
private:
  std::string _name;
  std::vector <Variable*> _variablesCollection;
  std::vector <Constraint *> _constraintsCollection;
   
  unsigned int minArity;
  unsigned int maxArity;

public:
  Problem ();

  bool consolidateVariables();
  bool consolidateConstraints();  
  
  void setName (const std::string &name);

  void addVariableAtIndex (Variable *variable,int index);
  void initVariables(int nbVariables);
 
  void addConstraintAtIndex (Constraint *constraint, int index);  
  void initConstraints(int nbConstraints);
  
  Variable &getVariable (int variableIndex) const;
  
  std::vector <Constraint *> const &getConstraintsCollection () const;
  std::vector <Variable *> const &getVariablesCollection () const;

  unsigned int getNbVariables () const;
  unsigned int getNbConstraints () const;

  unsigned int getMinArity () const;
  unsigned int getMaxArity () const;

  void display () const;
};

#endif
