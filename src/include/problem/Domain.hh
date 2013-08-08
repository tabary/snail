#ifndef DEF_DOMAIN
#define DEF_DOMAIN

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cassert>

class Domain
{
private:
  const std::string _name;
  unsigned int _id;
  
  std::vector<int> _initialDomain;
  std::vector<int> _currentDomain;
  
  int* _removalsStack[2]; // i=0 => index  
                                       // i=1 => depth
  int _nbRemovals;

  int _firstPresentIndex;
  int _lastPresentIndex;
  int* _forwardCurrentDomain;
  int* _backwardCurrentDomain;



public:
  Domain (std::string const &name,int idDomain, int min, int max, int nbValues); // Limits are included
  Domain (std::string const &name, int idDomain, int nbValues);

  Domain (Domain const &d);

  ~Domain();
  
  void addValue (int v);
  void addIntervalValue (int min, int max); // Limits are included

  unsigned int getDomainId() const;
  
  const std::vector<int>  &getInitialDomain () const;
  const std::vector<int>  &getCurrentDomain () const;

  bool isPresent (int i) const;

  int getNbRemovals () const;
  int getNbInitialValues () const;
  int getNbCurrentValues () const;

  int getValueOfIndex (int index) const;
  int getFirstPresentIndex () const;
  int getUniquePresentValue () const;
  int getUniquePresentIndex () const;
  
  
  int getNextPresentIndexAfter(int index) const;

  void reduceToIndexAtDepth (int valueIndex, int depth);
  void removeIndexAtDepth (int valueIndex, int depth);

  void restoreAllIndexAtDepth (int depth);
  void restoreUniqueIndexAtDepth (int index, int depth);

  
  
  
  friend std::ostream& operator<< (std::ostream &flux, const Domain &domain);
};


#endif
