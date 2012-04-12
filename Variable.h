#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.h"

class Variable
{
 private :
  std::string d_name; 
  Domain &d_domain;

  static int nbAssigned;

  bool assigned;

 public :
  Variable(std::string name, Domain &domain); // The associated domain must be previously created
  
  static int getNbAssigned();

  Domain &getDomain();
  std::string  &getName() ; 
  bool isAssigned();
  void setAssigned(bool a);

  bool hasEmptyDomain();

  friend std::ostream& operator<<(std::ostream &flux, const Variable &variable);
};


#endif
