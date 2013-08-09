#include "Constraint.hh"

using namespace std;

Constraint::Constraint (const string &name, Relation &relation, int arity, int id) : _name (name), _relation (relation), _arity (arity), _nbUnassignedVariable (arity), _id(id) 
{
  assert (_arity > 0);
  myTupleValue=new int[_arity];
  myTupleIndex=new int[_arity];
 }

unsigned int 
Constraint::getIndex () const
{
   return _id;
}

std::string const &
Constraint::getName () const
{
  return _name;
}

bool
Constraint::isConsistent () const
{
  for (size_t i = 0; i < _arity; ++i)
    {
      if (_scope[i]->hasEmptyDomain ())
        return false;
      if (!_scope[i]->isAssigned ())
        return true;
      myTupleValue[i] = (_scope[i]->getDomain ()).getUniquePresentValue ();
    }
  if (isValid (myTupleValue))
    return true;
  return false;
}





bool
Constraint::isValid (snail::tuple const t) const
    {
    return  (_relation.getRelType() == REL_CONFLICT ? !_relation.isPresent (t) : _relation.isPresent (t));
    }



 
 /*
 bool
Constraint::seekSupport (Variable& x, int indexValue)
{
  // enumerate the cartesien product of the domains
   // and for each check if at least one is consistent 
   //
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
      if (isValid(myTuple))
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
*/
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

unsigned int
Constraint::getArity ()
{
  return _arity;
}

void
Constraint::addVariableToScope (Variable *variable)
{
  _scope.push_back (variable);
}

const  snail::tuple &
Constraint::getMyTupleValue ()
{
  return myTupleValue;
}

const  snail::tuple &
Constraint::getMyTupleIndex ()
{
  return myTupleIndex;
}


ostream& operator<< (ostream &flux, const Constraint &constraint)
{
  flux << constraint._name << " (id=" << constraint._id <<") [";
  for (size_t i(0); i < constraint._arity; ++i)
    {
      flux << constraint._scope[i]->getName () << ( i+1 == constraint._arity  ? "" : ",");
    }
  flux << "] with relation " << constraint._relation ;
  return flux;
}
