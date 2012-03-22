#include "Domain.h"

using namespace std;


Domain::Domain(string name, int min, int max) : d_name(name)
{
  assert(max >= min);
  for(int i=min; i<= max; i++)
    d_initialDomain.push_back(i);
  d_currentDomain.insert(d_currentDomain.begin(),d_initialDomain.size(),-1);
} 

vector<int> const &Domain::getInitialDomain() const
{
  return d_initialDomain;
}

vector<int> const &Domain::getCurrentDomain() const
{
  return d_currentDomain;
}

int Domain::getValueOfIndex(int index)
{
  assert(index < (int)d_initialDomain.size() && index >= 0);
  return d_initialDomain[index];
}


void Domain::reduceToIndexAtDepth(int indexValue, int depth)
{
  for(int i=0; i<(int)d_currentDomain.size(); i++)
    if (d_currentDomain[i] == -1 && i != indexValue)
      d_currentDomain[i] = depth;
}


ostream& operator<<(ostream &flux, const Domain &domain)
{
  assert(domain.d_initialDomain.size()!=0);
  flux << domain.d_name << ":[" ;
  for (unsigned int i=0; i<domain.d_initialDomain.size(); i++){
    flux << domain.d_initialDomain[i] ;
    flux << (i!=domain.d_initialDomain.size()-1 ? "," : "") ;
  }
  flux << "]" ;
  return flux;
}
