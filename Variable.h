#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.h"

class Variable
{
 private :
  std::string d_name; 
  int d_variableId;
  
  Domain &d_domain;

  static int nbAssigned;

  bool assigned;

 public :
  Variable(std::string name, Domain &domain, int variableId = -1); // The associated domain must be previously created
  
  static int getNbAssigned();
  static void setNbAssigned(int nb);
  
  Domain &getDomain();
  std::string  &getName() ; 
 
  bool isAssigned();
  void setAssigned(bool a);

  bool hasEmptyDomain();

  friend std::ostream& operator<<(std::ostream &flux, const Variable &variable);
};


#endif
