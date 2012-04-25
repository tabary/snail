#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.h"

class Variable {
private:
    static int nbAssigned;
    
    std::string _name;
    int _Id;

    Domain &_domain;
  
    bool _assigned;

public:
    Variable(const std::string &name, Domain &domain, int variableId = -1); // The associated domain must be previously created

    static int getNbAssigned();
    static void setNbAssigned(int nb);

    Domain &getDomain();
    std::string const &getName() const;

    bool isAssigned() const;
    void setAssigned(bool a);

    bool hasEmptyDomain() const;

    friend std::ostream& operator<<(std::ostream &flux, const Variable &variable);
};

#endif
