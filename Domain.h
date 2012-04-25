#ifndef DEF_DOMAIN
#define DEF_DOMAIN

#include <iostream>
#include <vector>
#include <assert.h>

class Domain {
private:
    std::string _name;
    std::vector<int> _initialDomain;
    std::vector<int> _currentDomain;
    int _nbRemovals;

public:
    Domain(const std::string &name, int min, int max); // Limits are included
    Domain(const std::string & name);

    void addValue(int v);
    void addIntervalValue(int min, int max); // Limits are included

    std::vector<int> const &getInitialDomain() const;
    std::vector<int> const &getCurrentDomain() const;

    int getNbRemovals() const;
    int getNbInitialValues() const;

    int getValueOfIndex(int index) const;
    int getFirstPresent() const;
    int getUniquePresent() const;

    void reduceToIndexAtDepth(int valueIndex, int depth);
    void removeIndexAtDepth(int valueIndex, int depth);

    void restoreAllIndexAtDepth(int depth);
    void restoreUniqueIndexAtDepth(int index, int depth);

    friend std::ostream& operator<<(std::ostream &flux, const Domain &domain);
};


#endif
