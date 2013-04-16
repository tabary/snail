#include "Domain.h"

using namespace std;

Domain::Domain (string const &name, int min, int max, int nbValues) : _name (name), _nbRemovals (0), _firstPresentIndex(0), _lastPresentIndex(nbValues-1)
{
  assert (max >= min && (max-min+1) == nbValues);
  for (int i = min; i <= max; ++i)
    _initialDomain.push_back (i);
  _currentDomain.insert (_currentDomain.begin (), _initialDomain.size (), -1);
  _removalsStack[0] = new int [nbValues];
  _removalsStack[1] = new int [nbValues];
  
  _forwardCurrentDomain = new int[nbValues];
  _backwardCurrentDomain = new int[nbValues];
  
  for(int i=0; i< nbValues; ++i){
      _forwardCurrentDomain[i]=i+1;
      _backwardCurrentDomain[i] = i-1;
    }
  _forwardCurrentDomain[nbValues-1]=-1;
  _backwardCurrentDomain[0] = -1;
}

Domain::Domain (string const &name, int nbValues) : _name (name), _nbRemovals (0), _firstPresentIndex(-1), _lastPresentIndex(-1)
{
  _removalsStack[0] = new int [nbValues];
  _removalsStack[1] = new int [nbValues];

  _forwardCurrentDomain = new int[nbValues];
  _backwardCurrentDomain = new int[nbValues];
}

Domain::Domain (const Domain& d) : _name (d._name), _initialDomain (d._initialDomain), _currentDomain (d._currentDomain), _nbRemovals (d._nbRemovals),_firstPresentIndex(d._firstPresentIndex), _lastPresentIndex(d._lastPresentIndex) 
{
  _removalsStack[0] = new int [_initialDomain.size ()];
  _removalsStack[1] = new int [_initialDomain.size ()];

  memcpy (_removalsStack[0], d._removalsStack[0], _initialDomain.size () * sizeof (int));
  memcpy (_removalsStack[1], d._removalsStack[1], _initialDomain.size () * sizeof (int));

  _forwardCurrentDomain = new int [_initialDomain.size()];
  _backwardCurrentDomain = new int [_initialDomain.size()];

  memcpy (_forwardCurrentDomain, d._forwardCurrentDomain, _initialDomain.size () * sizeof (int));
  memcpy (_backwardCurrentDomain, d._backwardCurrentDomain, _initialDomain.size () * sizeof (int));
}

void
Domain::addValue (int v)
{  
  assert(_forwardCurrentDomain != NULL && _backwardCurrentDomain != NULL);
  
  _initialDomain.push_back (v);
  _currentDomain.push_back (-1);
  
  if (_firstPresentIndex == -1 && _lastPresentIndex == -1){
    _firstPresentIndex = 0;
    _lastPresentIndex = 0;
    _forwardCurrentDomain[0]= -1;
    _backwardCurrentDomain[0]= -1;
    }
  else
    {
      assert(_lastPresentIndex+1 ==_initialDomain.size ()-1 );
      _forwardCurrentDomain[_lastPresentIndex]=_initialDomain.size ()-1 ;
      _forwardCurrentDomain[_initialDomain.size ()-1]= -1;
      
      _backwardCurrentDomain[_initialDomain.size ()-1]=_lastPresentIndex ;
    
      _lastPresentIndex = _initialDomain.size ()-1;
    }
}



void
Domain::addIntervalValue (int min, int max)
{
  assert (max >= min);
  for (int i = min; i <= max; i++)
    {
      addValue(i);
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
Domain::getFirstPresentIndex () const
{
  return _firstPresentIndex;
}

int
Domain::getUniquePresentValue () const
{
  assert (_nbRemovals == (int) _currentDomain.size () - 1);
  assert (_firstPresentIndex == _lastPresentIndex);
  assert ( _forwardCurrentDomain[_firstPresentIndex]==-1 && _backwardCurrentDomain[_firstPresentIndex]==-1);
  return _initialDomain[_firstPresentIndex];
}

int
Domain::getUniquePresentIndex () const
{
  assert (_nbRemovals == (int) _currentDomain.size () - 1);
  assert (_firstPresentIndex == _lastPresentIndex);
  assert ( _forwardCurrentDomain[_firstPresentIndex]==-1 && _backwardCurrentDomain[_firstPresentIndex]==-1);
  return _firstPresentIndex;
}


int
Domain::getNextPresentIndexAfter(int index) const
{
  assert(_currentDomain[index] == -1);
  return _forwardCurrentDomain[index];
}

void
Domain::reduceToIndexAtDepth (int indexValue, int depth)
{
  assert(_firstPresentIndex != -1 && _lastPresentIndex != -1 && indexValue >= _firstPresentIndex && indexValue <= _lastPresentIndex);
   
  int i = _firstPresentIndex;  
  while (i != indexValue){
      _currentDomain[i] = depth;
      _removalsStack[0][_nbRemovals] = i;
      _removalsStack[1][_nbRemovals] = depth;
      _nbRemovals++;
      i = _forwardCurrentDomain[i];
     }
  _firstPresentIndex = indexValue;
  _forwardCurrentDomain[indexValue] = -1;
 i = _lastPresentIndex;  
  while (i != indexValue){
      _currentDomain[i] = depth;
      _removalsStack[0][_nbRemovals] = i;
      _removalsStack[1][_nbRemovals] = depth;
      _nbRemovals++;
      i = _backwardCurrentDomain[i];
     }
  _lastPresentIndex = indexValue;
  _backwardCurrentDomain[indexValue] = -1;  
}

void
Domain::removeIndexAtDepth (int indexValue, int depth)
{
  assert (_currentDomain[indexValue] == -1 && !(_firstPresentIndex==-1 && _lastPresentIndex==-1));
  _currentDomain[indexValue] = depth;
  _removalsStack[0][_nbRemovals] = indexValue;
  _removalsStack[1][_nbRemovals] = depth;
  _nbRemovals++;
  
  if (_firstPresentIndex == indexValue && _lastPresentIndex == indexValue){
      _firstPresentIndex = -1;
      _lastPresentIndex = -1;
      return;
    }
  
  if (_firstPresentIndex == indexValue){
      _backwardCurrentDomain[_forwardCurrentDomain[indexValue]] = -1;
      _firstPresentIndex = _forwardCurrentDomain[indexValue];
      return;
    }
  
  if (_lastPresentIndex == indexValue){
      _forwardCurrentDomain[_backwardCurrentDomain[indexValue]] = -1;
      _lastPresentIndex = _backwardCurrentDomain[indexValue];
      return;
    }
  
      _forwardCurrentDomain[_backwardCurrentDomain[indexValue]] = _forwardCurrentDomain[indexValue];
      _backwardCurrentDomain[_forwardCurrentDomain[indexValue]] = _backwardCurrentDomain[indexValue];
}

void
Domain::restoreAllIndexAtDepth (int depth)
{
  int index;
  while (_nbRemovals != 0 && _removalsStack[1][_nbRemovals - 1] == depth)
    {
      index = _removalsStack[0][_nbRemovals - 1];
      restoreUniqueIndexAtDepth(index,depth);
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
  
  if (  _firstPresentIndex == -1 &&  _lastPresentIndex == -1){
      _firstPresentIndex = index;
      _lastPresentIndex = index;
      _forwardCurrentDomain[index] = -1;
      _backwardCurrentDomain[index] = -1;
      return;
    }
  
  if (index < _firstPresentIndex){
      _forwardCurrentDomain[index] = _firstPresentIndex;
      _backwardCurrentDomain[index] = -1;
      _backwardCurrentDomain[_firstPresentIndex] = index;
      _firstPresentIndex = index;
      return;
    }
  
  if (index > _lastPresentIndex){ 
     _backwardCurrentDomain[index] = _lastPresentIndex;
      _forwardCurrentDomain[index] = -1;
      _forwardCurrentDomain[_lastPresentIndex] = index;
      _lastPresentIndex = index;
      return;
    }
  
  for(int i= index+1; i <= _lastPresentIndex; ++i){
      if (_currentDomain[i] == -1){
          _forwardCurrentDomain[index] = i;
          _forwardCurrentDomain[_backwardCurrentDomain[i]]= index;
          _backwardCurrentDomain[index] = _backwardCurrentDomain[i];
          _backwardCurrentDomain[i] = index;
          return;
        }
    }
  
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
