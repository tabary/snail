#ifndef DEF_DOMAIN
#define DEF_DOMAIN

#include <iostream>
#include <vector>
#include <assert.h>

class Domain
{
 public :
  Domain(std::string name, int min, int max); // Limits are included
 
  friend std::ostream& operator<<(std::ostream &flux, const Domain &domain);

 private :
  std::string d_name; 
  std::vector<int> d_initialDomain;
  std::vector<int> d_currentDomain;
};


#endif
