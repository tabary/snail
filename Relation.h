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

  bool isEqual(tuple const t1, tuple const t2) const;

 public :
  Relation(std::string name, int tupleSize); 
  void addTuple(tuple const t);

  bool isValid(tuple const t) const;

  std::string & getName(); 
  
  
  friend std::ostream& operator<<(std::ostream &flux, const Relation &relation);

};


#endif
