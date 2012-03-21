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
