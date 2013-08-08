#ifndef DEF_RELATION
#define DEF_RELATION

#include <iostream>
#include <vector>
#include <string.h>

#include <cassert>
#include "parser/XMLParser_constants.h"

#include "global.hh"

class Relation
{
private:
  const std::string _name;
  RelType _relType;
    
  std::vector<snail::tuple> _tuplesCollection;
  unsigned int _tupleSize;

  bool isEqual(const snail::tuple t1, const snail::tuple t2) const;

public:
  Relation (const std::string &name, RelType relType, int tupleSize, int nbTuples);
  ~Relation();

  void addTuple (const snail::tuple t);


  const std::vector<snail::tuple>& getTuplesCollection() const;
  RelType getRelType() const;
  const std::string & getName () const;

  bool isPresent(snail::tuple t) const ;
  
  
  friend std::ostream& operator<< (std::ostream &flux, const Relation &relation);

};


#endif
