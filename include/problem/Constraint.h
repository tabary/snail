#ifndef DEF_CONSTRAINT
#define DEF_CONSTRAINT

#include "Relation.h"
#include "Variable.h"

#include <cassert>

class Variable;


class Constraint
{
private:
  
  
  std::string _name;
  int _id;
  
  int _arity;
  int _relType;
  
  int _nbUnassignedVariable;

  std::vector <Variable *> _scope;
  
  
  Relation* _relation;
  std::vector<tuple> _table;
  
  tuple myTuple; // temporary tuple
  tuple myIndexTuple; // temporary tuple of value indexes 

  
  bool isEqual (tuple const t1, tuple const t2) const;
  bool isPresent (tuple const t) const;
  
  
  
  public:
  Constraint (const std::string &name, int arity, Relation* relation); // The associated domain must be previously created
 
  void consolidate(int id);
  
  int getIndex () const;
    
  std::string const &getName () const;
  
  bool isConsistent () const;
  bool isValid (tuple t) const;
  bool seekSupport(Variable &x, int indexValue);
  
 
  bool isCovered () const;

  void incNbUnassignedVariable ();
  void decNbUnassignedVariable ();

  std::vector <Variable *> const &getScope () const;

  int getArity ();

  void addVariableToScope (Variable *variable);

  tuple &getMyTuple ();

  friend std::ostream& operator<< (std::ostream &flux, const Constraint &constraint);
};

#endif
