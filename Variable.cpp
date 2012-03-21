#include "Variable.h"

using namespace std;


Variable::Variable(string name, Domain &domain) : d_name(name), d_domain(domain)
{
} 

ostream& operator<<(ostream &flux, const Variable &variable)
{
  flux << variable.d_name << " with associated domain " << variable.d_domain ;
  return flux;
}
