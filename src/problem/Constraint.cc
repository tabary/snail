#include "Constraint.h"

using namespace std;

Constraint::Constraint (const string &name, int arity, Relation const &relation) : _name (name), _arity (arity), _nbUnassignedVariable (arity), _relation (relation)
{
  assert (_arity >= 1);
  myTuple = new int[_arity];
  myIndexTuple = new int[_arity];
}


int 
Constraint::getIndex () const
{
   return _id;
}

void
Constraint::setIndex (int id)
{
  _id = id;
}

std::string const &
Constraint::getName () const
{
  return _name;
}

bool
Constraint::isConsistent () const
{
  for (int i = 0; i < _arity; ++i)
    {
      if (_scope[i]->hasEmptyDomain ())
        return false;
      if (!_scope[i]->isAssigned ())
        return true;
      myTuple[i] = (_scope[i]->getDomain ()).getUniquePresentValue ();
    }
  if (_relation.isValid (myTuple))
    return true;
  return false;
}

bool
Constraint::isValid (tuple t) const
{
  return _relation.isValid (t);
}


bool
Constraint::seekSupport (Variable& x, int indexValue)
{
  /* enumerate the cartesien product of the domains
   * and for each check if at least one is consistent 
   */
  int cptSkipped;
    
  for (unsigned int i = 0; i < _scope.size (); ++i)
    {
      
      if (_scope[i] == &x){
          cptSkipped = i;
          myIndexTuple[i]=indexValue;
          myTuple[i] = x.getDomain ().getValueOfIndex (indexValue);
        }
      else {
          myIndexTuple[i] =_scope[i]->getDomain ().getFirstPresentIndex (); 
          myTuple[i] = _scope[i]->getDomain ().getValueOfIndex (myIndexTuple[i]);
        }
    }
  
  int cpt (_scope.size ()-1);
  int index;
  Variable* v;
  
  while (cpt != -1)
    {
      if (_relation.isValid(myTuple))
        return true;
      
        if (cpt != cptSkipped){
            v = _scope[cpt];
            index = v->getDomain ().getNextPresentIndexAfter (myIndexTuple[cpt]);
            if (index != -1){
                myIndexTuple[cpt] = index;
                myTuple[cpt] = v->getDomain ().getValueOfIndex (index);
                continue;
              }
          }
            
        do{
            --cpt;           
            if (cpt == -1)
              break;
            
            v = _scope[cpt];
            if (cpt != cptSkipped)
              index = v->getDomain ().getNextPresentIndexAfter (myIndexTuple[cpt]);
            else
              index = -1;
          }while (index == -1);
      
          if (cpt != -1){
              v = _scope[cpt];
              myIndexTuple[cpt] = index;
              myTuple[cpt] = v->getDomain ().getValueOfIndex (index);
              for (int i=cpt+1; i < _scope.size (); ++i){
                  if (i == cptSkipped)
                    continue;
                  myIndexTuple[i] = _scope[i]->getDomain ().getFirstPresentIndex (); 
                  myTuple[i] = _scope[i]->getDomain ().getValueOfIndex (myIndexTuple[i]);
                }
              cpt = _scope.size ()-1;
            }
    }
  return false;
}

bool
Constraint::isCovered () const
{
  return (_nbUnassignedVariable == 0 ? true : false);
}

void
Constraint::incNbUnassignedVariable ()
{
  _nbUnassignedVariable++;
}

void
Constraint::decNbUnassignedVariable ()
{
  _nbUnassignedVariable--;
}

std::vector <Variable *> const &
Constraint::getScope () const
{
  return _scope;
}

int
Constraint::getArity ()
{
  return _arity;
}

void
Constraint::addVariableToScope (Variable *variable)
{
  _scope.push_back (variable);
}

tuple &
Constraint::getMyTuple ()
{
  return myTuple;
}

ostream& operator<< (ostream &flux, const Constraint &constraint)
{
  flux << constraint._name << " [";
  for (int i = 0; i < constraint._arity; i++)
    {
      flux << constraint._scope[i]->getName () << (i < constraint._arity - 1 ? "," : "");
    }
  flux << "] with associated relation " << constraint._relation;
  return flux;
}
