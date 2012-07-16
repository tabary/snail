#include "Relation.h"

using namespace std;


Relation::Relation(const string &name, int tupleSize, int relType) : _name(name), _tupleSize(tupleSize)
{
  assert(_tupleSize > 0);
   switch(relType)
    {
    case 0:
        _relType = REL_SUPPORT;
        break;
    case 1:
        _relType = REL_CONFLICT;
        break;
    default:
      throw ("unknown relation type");
    }
} 

void Relation::addTuple(tuple const t)
{
  assert(t != NULL && _tupleSize > 0);
  tuple myTuple= new int[_tupleSize];
  memcpy(myTuple,t,sizeof(t[0])*_tupleSize);
  _tuplesCollection.push_back(myTuple);
}

bool Relation::isEqual(tuple const t1, tuple const t2) const
{
  for(int j=0; j<_tupleSize; ++j){
      if (t1[j] == -1 || t2[j] == -1)
          continue;
      if (t1[j] != t2[j])
          return false;
  }
  return true;
}

bool Relation::isValid(tuple const t) const
{
    return (_relType == REL_SUPPORT ? isPresent(t) : !isPresent(t));    
}

bool Relation::isPresent(tuple const t) const
{
  for(unsigned int i=0; i<_tuplesCollection.size(); ++i){
    if (isEqual(_tuplesCollection[i],t))
      return true;
  }
  return false;    
}

const string&  Relation::getName()
{
    return _name;
}

ostream& operator<<(ostream &flux, const Relation &relation)
{
  flux << relation._name << ":" ;
  for(unsigned int i=0; i<relation._tuplesCollection.size(); i++){
    flux << "(";
    for(int j=0; j<relation._tupleSize; j++){
      flux << relation._tuplesCollection[i][j] << (j<relation._tupleSize-1 ? "," : "");
    }
    flux <<")" << (i<relation._tuplesCollection.size()-1 ? "," : "") ;
  }
  return flux;
}
