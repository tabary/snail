#ifndef DEF_RELATION
#define DEF_RELATION

#include <iostream>
#include <vector>
#include <assert.h>

typedef int* tuple;

class Relation
{
 private :
  std::string _name;
  std::vector<tuple> _tuplesCollection;
  int _tupleSize;

  enum relationType {REL_CONFLICT, REL_SUPPORT, REL_SOFT};
  relationType  _relType; 
  
  bool isEqual(tuple const t1, tuple const t2) const;
  bool isPresent(tuple const t) const;
  
 public :
  Relation(const std::string &name, int tupleSize, int relType); 
  
  void addTuple(tuple const t);

  bool isValid(tuple const t) const;

  const std::string & getName(); 
    
  friend std::ostream& operator<<(std::ostream &flux, const Relation &relation);

};


#endif
