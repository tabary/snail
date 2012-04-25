#include "Domain.h"

using namespace std;


Domain::Domain(const string &name, int min, int max) : _name(name), _nbRemovals(0)
{
  assert(max >= min);
  for(int i=min; i<= max; ++i)
    _initialDomain.push_back(i);
  _currentDomain.insert(_currentDomain.begin(),_initialDomain.size(),-1);
} 

Domain::Domain(const string &name) : _name(name), _nbRemovals(0)
{
}

void Domain::addValue(int v)
{
    _initialDomain.push_back(v);
    _currentDomain.push_back(-1);
}

void Domain::addIntervalValue(int min, int max)
{
    assert(max >= min);
      for(int i=min; i<= max; i++){
          _initialDomain.push_back(i);
          _currentDomain.push_back(-1);
      }
}

vector<int> const &Domain::getInitialDomain() const
{
  return _initialDomain;
}

vector<int> const &Domain::getCurrentDomain() const
{
  return _currentDomain;
}

int Domain::getNbRemovals() const
{
  return _nbRemovals;
}

int Domain::getNbInitialValues() const
{
  return _initialDomain.size();
}

int Domain::getValueOfIndex(int index) const
{
  assert(index < (int)_initialDomain.size() && index >= 0);
  return _initialDomain[index];
}

int Domain::getFirstPresent() const
{
  for(unsigned int i=0; i<_currentDomain.size(); ++i)
    if (_currentDomain[i]==-1)
      return i;
  throw("Unreachable Code");
}

int Domain::getUniquePresent() const
{
  assert(_nbRemovals == (int)_currentDomain.size()-1);
  for(int i=0; i<(int)_currentDomain.size(); ++i)
    if (_currentDomain[i] == -1)
      return _initialDomain[i];
  throw("Unreachable Code");
}

void Domain::reduceToIndexAtDepth(int indexValue, int depth)
{
  for(int i=0; i<(int)_currentDomain.size(); ++i)
    if (_currentDomain[i] == -1 && i != indexValue){
      _currentDomain[i] = depth;
      _nbRemovals++;
    }
}

void Domain::removeIndexAtDepth(int indexValue, int depth)
{
  assert(_currentDomain[indexValue] == -1);
  _currentDomain[indexValue] = depth;
  _nbRemovals++;
} 


void Domain::restoreAllIndexAtDepth(int depth)
{
  for(int i=0; i<(int)_currentDomain.size(); ++i)
    if (_currentDomain[i] == depth){
      _currentDomain[i] = -1;
      _nbRemovals--;
    }
}

void Domain::restoreUniqueIndexAtDepth(int index, int depth)
{
  assert (_currentDomain[index] == depth);
  _currentDomain[index] = -1;
  _nbRemovals--;
}


ostream& operator<<(ostream &flux, const Domain &domain)
{
  assert(domain._currentDomain.size()!=0);
  flux << domain._name << ":[" ;
  for (unsigned int i=0; i<domain._currentDomain.size(); ++i){
    flux << domain._currentDomain[i] ;
    flux << (i!=domain._currentDomain.size()-1 ? "," : "") ;
  }
  flux << "]" ;
  return flux;
}
