#include "Domain.h"

using namespace std;

Domain::Domain (string const &name, int min, int max, int nbValues) : _name (name), _nbRemovals (0)
{
  assert (max >= min);
  for (int i = min; i <= max; ++i)
    _initialDomain.push_back (i);
  _currentDomain.insert (_currentDomain.begin (), _initialDomain.size (), -1);
  _removalsStack[0] = new int [nbValues];
  _removalsStack[1] = new int [nbValues];
}

Domain::Domain (string const &name, int nbValues) : _name (name), _nbRemovals (0)
{
  _removalsStack[0] = new int [nbValues];
  _removalsStack[1] = new int [nbValues];
}

Domain::Domain (const Domain& d) : _name (d._name), _initialDomain (d._initialDomain), _currentDomain (d._currentDomain), _nbRemovals (d._nbRemovals)
{
  _removalsStack[0] = new int [_initialDomain.size ()];
  _removalsStack[1] = new int [_initialDomain.size ()];

  memcpy (_removalsStack[0], d._removalsStack[0], _initialDomain.size () * sizeof (int));
  memcpy (_removalsStack[1], d._removalsStack[1], _initialDomain.size () * sizeof (int));
}

void
Domain::addValue (int v)
{
  _initialDomain.push_back (v);
  _currentDomain.push_back (-1);
}

void
Domain::addIntervalValue (int min, int max)
{
  assert (max >= min);
  for (int i = min; i <= max; i++)
    {
      _initialDomain.push_back (i);
      _currentDomain.push_back (-1);
    }
}

vector<int> const &
Domain::getInitialDomain () const
{
  return _initialDomain;
}

vector<int> const &
Domain::getCurrentDomain () const
{
  return _currentDomain;
}

bool
Domain::isPresent (int i) const
{
  return (_currentDomain[i] == -1 ? true : false);
}

int
Domain::getNbRemovals () const
{
  return _nbRemovals;
}

int
Domain::getNbInitialValues () const
{
  return _initialDomain.size ();
}

int
Domain::getNbCurrentValues () const
{

  return (_initialDomain.size () - _nbRemovals);
}

int
Domain::getValueOfIndex (int index) const
{
  assert (index < (int) _initialDomain.size () && index >= 0);
  return _initialDomain[index];
}

int
Domain::getFirstPresent () const
{
  for (unsigned int i = 0; i < _currentDomain.size (); ++i)
    if (_currentDomain[i] == -1)
      return i;
  throw ("Unreachable Code");
}

int
Domain::getUniquePresentValue () const
{
  return _initialDomain[getUniquePresentIndex()];
}

int
Domain::getUniquePresentIndex () const
{
  assert (_nbRemovals == (int) _currentDomain.size () - 1);
  for (unsigned int i = 0; i <  _currentDomain.size (); ++i)
    if (_currentDomain[i] == -1)
      return i;
  throw ("Unreachable Code");
}


int
Domain::getNextPresentIndexAfter(int index) const
{
  for (unsigned int i = index+1; i <  _currentDomain.size (); ++i)
    if (_currentDomain[i] == -1)
      return i;
  return -1;
}

void
Domain::reduceToIndexAtDepth (int indexValue, int depth)
{
  for (int i = 0; i < (int)  _currentDomain.size (); ++i)
    if (_currentDomain[i] == -1 && i != indexValue)
      {
        _currentDomain[i] = depth;
        _removalsStack[0][_nbRemovals] = i;
        _removalsStack[1][_nbRemovals] = depth;
        _nbRemovals++;
      }
}

void
Domain::removeIndexAtDepth (int indexValue, int depth)
{
  assert (_currentDomain[indexValue] == -1);
  _currentDomain[indexValue] = depth;
  _removalsStack[0][_nbRemovals] = indexValue;
  _removalsStack[1][_nbRemovals] = depth;
  _nbRemovals++;
}

void
Domain::restoreAllIndexAtDepth (int depth)
{
  int index;
  while (_nbRemovals != 0 && _removalsStack[1][_nbRemovals - 1] == depth)
    {
      index = _removalsStack[0][_nbRemovals - 1];
      _currentDomain[index] = -1;
      _nbRemovals--;
    }
}

void
Domain::restoreUniqueIndexAtDepth (int index, int depth)
{
  assert (_currentDomain[index] == depth);
  int i = _removalsStack[0][_nbRemovals - 1];
  assert (i == index); // The top of the removalsStack must be the index to restore
  _currentDomain[index] = -1;
  _nbRemovals--;
}


ostream& operator<< (ostream &flux, const Domain &domain)
{
  assert (domain._currentDomain.size () != 0);
  flux << domain._name << ":[";
  for (unsigned int i = 0; i < domain._currentDomain.size (); ++i)
    {
      flux << domain._currentDomain[i];
      flux << (i != domain._currentDomain.size () - 1 ? "," : "");
    }
  flux << "]";
  return flux;
}
