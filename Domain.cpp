#include "Domain.h"

using namespace std;


Domain::Domain(string name, int min, int max) : d_name(name), nbRemovals(0)
{
  assert(max >= min);
  for(int i=min; i<= max; i++)
    d_initialDomain.push_back(i);
  d_currentDomain.insert(d_currentDomain.begin(),d_initialDomain.size(),-1);
} 

Domain::Domain(string name) : d_name(name), nbRemovals(0)
{
}


void Domain::addValue(int v)
{
    d_initialDomain.push_back(v);
    d_currentDomain.push_back(-1);
}

void Domain::addIntervalValue(int min, int max)
{
    assert(max >= min);
      for(int i=min; i<= max; i++){
          d_initialDomain.push_back(i);
          d_currentDomain.push_back(-1);
      }
}

vector<int> const &Domain::getInitialDomain() const
{
  return d_initialDomain;
}

vector<int> const &Domain::getCurrentDomain() const
{
  return d_currentDomain;
}


int const Domain::getNbRemovals()
{
  return nbRemovals;
}

int const Domain::getNbInitialValues()
{
  return d_initialDomain.size();
}

int Domain::getValueOfIndex(int index)
{
  assert(index < (int)d_initialDomain.size() && index >= 0);
  return d_initialDomain[index];
}

int Domain::getFirstPresentIndex() const
{
  for(unsigned int i=0; i<d_currentDomain.size(); i++)
    if (d_currentDomain[i]==-1)
      return i;
  assert(false);
  return -1;
}

int Domain::getUniqueValue() const
{
  assert(nbRemovals == (int)d_currentDomain.size()-1);
#ifdef TMPDEBUG
  int cpt(0);
  for(int i=0; i<(int)d_currentDomain.size(); i++)
    if (d_currentDomain[i] == -1) cpt++;
  assert(cpt == 1);
#endif
  for(int i=0; i<(int)d_currentDomain.size(); i++)
    if (d_currentDomain[i] == -1)
      return d_initialDomain[i];
  assert(false);
}


void Domain::reduceToIndexAtDepth(int indexValue, int depth)
{
  for(int i=0; i<(int)d_currentDomain.size(); i++)
    if (d_currentDomain[i] == -1 && i != indexValue){
      d_currentDomain[i] = depth;
      nbRemovals++;
    }
}

void Domain::removeIndex(int indexValue, int depth)
{
  assert(d_currentDomain[indexValue] == -1);
  d_currentDomain[indexValue] = depth;
  nbRemovals++;
} 


void Domain::restoreAllIndexAtDepth(int depth)
{
  for(int i=0; i<(int)d_currentDomain.size(); i++)
    if (d_currentDomain[i] == depth){
      d_currentDomain[i] = -1;
      nbRemovals--;
    }
}

void Domain::restoreUniqueIndexAtDepth(int index, int depth)
{
  assert (d_currentDomain[index] == depth);
  d_currentDomain[index] = -1;
  nbRemovals--;
}


ostream& operator<<(ostream &flux, const Domain &domain)
{
  assert(domain.d_currentDomain.size()!=0);
  flux << domain.d_name << ":[" ;
  for (unsigned int i=0; i<domain.d_currentDomain.size(); i++){
    flux << domain.d_currentDomain[i] ;
    flux << (i!=domain.d_currentDomain.size()-1 ? "," : "") ;
  }
  flux << "]" ;
  return flux;
}
