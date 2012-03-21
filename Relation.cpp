#include "Relation.h"

using namespace std;


Relation::Relation(string name) : d_name(name)
{
} 

void Relation::addTuple()
{
  int *t= new int[2];
  t[0] = 1;
  t[1] = 2;
  tuplesCollection.push_back(t);
}
