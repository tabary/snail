#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.h"

class Variable
{
 private :
  std::string d_name; 
  Domain &d_domain;

 public :
  Variable(std::string name, Domain &domain); // The associated domain must be previously created
  
  Domain &getDomain();

  friend std::ostream& operator<<(std::ostream &flux, const Variable &variable);
};


#endif
