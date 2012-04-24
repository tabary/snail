#include "Relation.h"

using namespace std;


Relation::Relation(string name, int tupleSize) : d_name(name), d_tupleSize(tupleSize)
{
  assert(d_tupleSize > 0);
} 

void Relation::addTuple(tuple const t)
{
  assert(t != NULL && d_tupleSize > 0);
  tuple myTuple= new int[d_tupleSize];
  memcpy(myTuple,t,sizeof(t[0])*d_tupleSize);
  d_tuplesCollection.push_back(myTuple);
}

bool Relation::isEqual(tuple const t1, tuple const t2) const
{
  for(int j=0; j<d_tupleSize; j++){
    if (t1[j] != t2[j])
      return false;
  }
  return true;
}

bool Relation::isValid(tuple const t) const
{
  for(unsigned int i=0; i<d_tuplesCollection.size(); i++){
    if (isEqual(d_tuplesCollection[i],t))
      return true;
  }
  return false;
}


string&  Relation::getName()
{
    return d_name;
}




ostream& operator<<(ostream &flux, const Relation &relation)
{
  flux << relation.d_name << ":" ;
  for(unsigned int i=0; i<relation.d_tuplesCollection.size(); i++){
    flux << "(";
    for(int j=0; j<relation.d_tupleSize; j++){
      flux << relation.d_tuplesCollection[i][j] << (j<relation.d_tupleSize-1 ? "," : "");
    }
    flux <<")" << (i<relation.d_tuplesCollection.size()-1 ? "," : "") ;
  }
  return flux;
}
