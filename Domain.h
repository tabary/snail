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
  int nbRemovals;

 public :
  Domain(std::string name, int min, int max); // Limits are included
  std::vector<int> const &getInitialDomain() const;
  std::vector<int> const &getCurrentDomain() const;

  int const getNbRemovals();
  int const getNbInitialValues();

  int getValueOfIndex(int index);
  int getFirstPresentIndex() const;
  int getUniqueValue() const;

  void reduceToIndexAtDepth(int valueIndex, int depth);
  void removeIndex(int valueIndex, int depth);

  void restoreAllIndexAtDepth(int depth);
  void restoreUniqueIndexAtDepth(int index, int depth);

  friend std::ostream& operator<<(std::ostream &flux, const Domain &domain);
};


#endif
