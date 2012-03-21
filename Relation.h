#ifndef DEF_RELATION
#define DEF_RELATION

#include <iostream>
#include <vector>
#include <assert.h>

typedef int* tuple;

class Relation
{
 private :
  std::string d_name;
  std::vector<tuple> d_tuplesCollection;
  int d_tupleSize;

 public :
  Relation(std::string name, int tupleSize); 
  void addTuple(tuple const t);
 
  friend std::ostream& operator<<(std::ostream &flux, const Relation &relation);

};


#endif
