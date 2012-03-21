#ifndef DEF_DOMAIN
#define DEF_DOMAIN

#include <iostream>
#include <vector>
#include <assert.h>

class Domain
{
 private :
  std::string d_name; 
  std::vector<int> d_initialDomain;
  std::vector<int> d_currentDomain;

 public :
  Domain(std::string name, int min, int max); // Limits are included
  std::vector<int> const &getInitialDomain() const;
  std::vector<int> const &getCurrentDomain() const;

  friend std::ostream& operator<<(std::ostream &flux, const Domain &domain);
};


#endif