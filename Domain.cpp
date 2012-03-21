#include "Domain.h"

using namespace std;


Domain::Domain(string name, int min, int max) : d_name(name)
{
  assert(max >= min);
  for(int i=min; i<= max; i++)
    d_initialDomain.push_back(i);
  d_currentDomain.insert(d_currentDomain.begin(),d_initialDomain.size(),-1);
} 

ostream& operator<<(ostream &flux, const Domain &domain)
{
  flux << domain.d_name << ":[" ;
  for (int i=0; i<domain.d_initialDomain.size(); i++){
    flux << domain.d_initialDomain[i] ;
    flux << (i!=domain.d_initialDomain.size()-1 ? "," : "") ;
  }
  flux << "]" ;
  return flux;
}
