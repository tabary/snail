#include "Variable.h"

using namespace std;


Variable::Variable(string name, Domain &domain) : d_name(name), d_domain(domain), assigned(false)
{
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
}

ostream& operator<<(ostream &flux, const Variable &variable)
{
  flux << variable.d_name << " with associated domain " << variable.d_domain ;
  return flux;
}
