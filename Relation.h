#ifndef DEF_RELATION
#define DEF_RELATION

#include <iostream>
#include <vector>

typedef int* tuple;

class Relation
{
 private :
  std::string d_name;
  std::vector<tuple> tuplesCollection;

 public :
  Relation(std::string name); 
  void addTuple();
 

};


#endif
