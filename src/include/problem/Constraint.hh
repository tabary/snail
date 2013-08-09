#ifndef DEF_CONSTRAINT
#define DEF_CONSTRAINT

#include "global.hh"
#include "Relation.hh"
#include "Variable.hh"

#include <cassert>

#include<string.h>


class Variable;


class Constraint
{
private:
 
  std::string _name;
 
  Relation&  _relation;
  snail::tuple myTupleValue; // temporary tuple
  snail::tuple myTupleIndex; // temporary tuple
  
  std::vector <Variable *> _scope;
  unsigned int _arity;
 
  unsigned int _nbUnassignedVariable;
  
  unsigned int _id;
  
 /* bool isEqual (tuple const t1, tuple const t2) const;
  bool isPresent (tuple const t) const;
  
  */
  
  public:
  Constraint (const std::string &name,  Relation& relation, int arity, int id); // The associated domain must be previously created
 
  unsigned int getIndex () const;
    
  std::string const &getName () const;
 
  bool isConsistent () const;
  bool isValid (snail::tuple const t) const;
  /*bool seekSupport(Variable &x, int indexValue);
  
 */
  bool isCovered () const;

  void incNbUnassignedVariable ();
  void decNbUnassignedVariable ();

  std::vector <Variable *> const &getScope () const;

  unsigned int getArity ();

  void addVariableToScope (Variable *variable);

  const snail::tuple  &getMyTupleValue ();
  const snail::tuple  &getMyTupleIndex ();

  friend std::ostream& operator<< (std::ostream &flux, const Constraint &constraint);
};

#endif
