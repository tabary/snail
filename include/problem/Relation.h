#ifndef DEF_RELATION
#define DEF_RELATION

#include <iostream>
#include <vector>
#include <string.h>

#include <cassert>
#include "parser/XMLParser_constants.h"

typedef int* tuple;

class Relation
{
private:
  std::string _name;
  std::vector<tuple> _tuplesCollection;
  int _tupleSize;

  
  RelType _relType;

public:
  Relation (const std::string &name, int tupleSize, RelType relType, int nbTuples);
  ~Relation();

  void addTuple (tuple const t);

  const std::vector<tuple>& getTuplesCollection() const;
  RelType getRelType() const;
//  bool isValid (tuple const t) const;

  const std::string & getName ();

  friend std::ostream& operator<< (std::ostream &flux, const Relation &relation);

};


#endif
