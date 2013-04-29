#include "Relation.h"

using namespace std;

Relation::Relation (const string &name, int tupleSize, RelType relType, int nbTuples) : _name (name), _tupleSize (tupleSize)
{
  assert (_tupleSize > 0);
  _relType = relType;  
}


Relation::~Relation ()
{
  for (unsigned int i = 0; i < _tuplesCollection.size (); ++i)
    {
      delete [] _tuplesCollection[i];     
    }
  _tuplesCollection.~vector ();
  _name.~basic_string ();
}


void
Relation::addTuple (tuple const t)
{
  assert (t != NULL && _tupleSize > 0);
  tuple myTuple = new int[_tupleSize];
  memcpy (myTuple, t, sizeof (t[0]) * _tupleSize);
  _tuplesCollection.push_back (myTuple);
}

 const std::vector<tuple>&
 Relation::getTuplesCollection() const 
 {
   return _tuplesCollection;
 }

 
const string&
Relation::getName ()
{
  return _name;
}

RelType Relation::getRelType() const
{
  return _relType;
}

ostream& operator<< (ostream &flux, const Relation &relation)
{
  flux << relation._name << ":";
  for (unsigned int i = 0; i < relation._tuplesCollection.size (); i++)
    {
      flux << "(";
      for (int j = 0; j < relation._tupleSize; j++)
        {
          flux << relation._tuplesCollection[i][j] << (j < relation._tupleSize - 1 ? "," : "");
        }
      flux << ")" << (i < relation._tuplesCollection.size () - 1 ? "," : "");
    }
  return flux;
}
