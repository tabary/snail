#include "Variable.h"

using namespace std;

int Variable::nbAssigned = 0;


Variable::Variable(string name, Domain &domain) : d_name(name), d_domain(domain), weightedDegree(0), assigned(false)
{
} 

int Variable::getNbAssigned()
{
  return nbAssigned;
}

 
Domain &Variable::getDomain()
{
  return d_domain;
}

string &Variable::getName() 
{
  return d_name;
}

bool Variable::isAssigned()
{
  return assigned;
}

void Variable::setAssigned(bool a)
{
  assigned = a;
  if (a==true)
    nbAssigned++;
  else 
    nbAssigned--;
}

void Variable::incrementWeightedDegree()
{
    weightedDegree++;
}

bool Variable::hasEmptyDomain()
{
  return (d_domain.getNbRemovals() == d_domain.getNbInitialValues());
}

ostream& operator<<(ostream &flux, const Variable &variable)
{
  flux << variable.d_name << " with associated domain " << variable.d_domain ;
  return flux;
}
