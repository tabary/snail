#include "Variable.h"

using namespace std;

int Variable::nbAssigned = 0;


Variable::Variable(string name, Domain &domain, int variableId ) : d_name(name), d_variableId(variableId), d_domain(domain), assigned(false)
{
} 

int Variable::getNbAssigned()
{
  return nbAssigned;
}

void Variable::setNbAssigned(int nb)
{
    nbAssigned = nb;
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

bool Variable::hasEmptyDomain()
{
  return (d_domain.getNbRemovals() == d_domain.getNbInitialValues());
}

ostream& operator<<(ostream &flux, const Variable &variable)
{
  flux << variable.d_name << " with associated domain " << variable.d_domain ;
  return flux;
}
