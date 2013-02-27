#include "Constraint.h"

using namespace std;

Constraint::Constraint (const string &name, int arity, Relation const &relation) : _name (name), _arity (arity), _nbUnassignedVariable (arity), _relation (relation)
{
  assert (_arity >= 1);
  myTuple = new int[_arity];
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
  int cpt (0);

  cerr << "Begin to seek a support for  " << x << " and for index " << indexValue << endl;


  cout << *this;
  
  
  for (unsigned int i = 0; i < _scope.size (); ++i)
    {
      _scope[i]->getDomain ().initIterator ();
      if (_scope[i]->getIndex () == x.getIndex ())
        myTuple[i] = x.getDomain ().getValueOfIndex (indexValue);
      cerr << *_scope[i] << endl;
    }

  while (cpt != -1)
    {
      cout << "cpt=" << cpt << endl;
      if (_scope[cpt]->getIndex () != x.getIndex ())
        {
          int index = _scope[cpt]->getDomain ().nextIterator ();
          cout << "value of index : " << index << endl ;
          if (index == -1)
            {
              --cpt;
              if(cpt !=-1 && _scope[cpt]->getIndex ()==x.getIndex ())
                --cpt;
              continue;
            }
          myTuple[cpt] = _scope[cpt]->getDomain ().getValueOfIndex (index);
        }
      cpt++;
      if (cpt == (int) _scope.size ())
        {
          cpt--;
          if(_scope[cpt]->getIndex ()==x.getIndex ())
            cpt--;

          cout << "tuple [";
          for (int i=0; i<_scope.size();i++)
            cout << myTuple[i]<<",";
          cout << "]" << endl;
       
          if (_relation.isValid(myTuple))
            return true;
                 
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
