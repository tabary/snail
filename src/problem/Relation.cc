#include "Relation.hh"

using namespace std;

Relation::Relation (const string &name, RelType relType, int tupleSize,  int nbTuples) : _name (name),  _relType(relType),   _tupleSize (tupleSize)
{
  assert (_tupleSize > 0);
}

Relation::~Relation ()
{
  for (size_t i(0); i < _tuplesCollection.size (); ++i)
    {
      delete [] _tuplesCollection[i];     
    }
   _name.~basic_string ();
}

bool
Relation::isEqual (const snail::tuple t1, const snail::tuple t2) const
{
  for (unsigned int j = 0; j < _tupleSize ; ++j)
    {
      if (t1[j] != t2[j])
        return false;
    }
  return true;
}

void
Relation::addTuple (const snail::tuple  t)
{
 #warning TODO assert : Check if the tuple is not already present
  assert (t != NULL);
  snail::tuple myTuple = new int[_tupleSize];
  memcpy (myTuple, t, sizeof (t[0]) * _tupleSize);
  _tuplesCollection.push_back (myTuple);
}

 const std::vector<snail::tuple>&
 Relation::getTuplesCollection() const 
 {
   return _tuplesCollection;
 }
 
const string&
Relation::getName () const
{
  return _name;
}

RelType Relation::getRelType() const
{
  return _relType;
}

bool
Relation::isPresent (snail::tuple t) const
{
  for(size_t i(0); i<_tuplesCollection.size (); ++i)
    {
      if (isEqual(t,_tuplesCollection[i]))
        return true;
    }
    return false;
}

ostream& operator<< (ostream &flux, const Relation &relation)
{
  flux << relation._name << ":";
  for (size_t i(0); i < relation._tuplesCollection.size (); i++)
    {
      flux << "(";
      for (size_t j(0); j < relation._tupleSize; j++)
        {
          flux << relation._tuplesCollection[i][j] << (j < relation._tupleSize - 1 ? "," : "");
        }
      flux << ")" << (i < relation._tuplesCollection.size () - 1 ? "," : "");
    }
  return flux;
}
