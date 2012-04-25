#include "Variable.h"

using namespace std;

int Variable::nbAssigned = 0;


Variable::Variable(const string &name, Domain &domain, int variableId ) : _name(name), _Id(variableId), _domain(domain), _assigned(false)
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
  return _domain;
}

string const &Variable::getName() const
{
  return _name;
}

bool Variable::isAssigned() const
{
  return _assigned;
}

void Variable::setAssigned(bool a)
{
    assert(_assigned != a);
  _assigned = a;
  if (a==true)
    nbAssigned++;
  else 
    nbAssigned--;
}

bool Variable::hasEmptyDomain() const
{
  return (_domain.getNbRemovals() == _domain.getNbInitialValues());
}

ostream& operator<<(ostream &flux, const Variable &variable)
{
  flux << variable._name << " with associated domain " << variable._domain ;
  return flux;
}
