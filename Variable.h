#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.h"
#include "Constraint.h"

class Constraint;

class Variable {
private:
    static int nbAssigned;
    
    std::string _name;
    int _Id;

    Domain &_domain;
    
     std::vector <Constraint *> _involvedConstraints;
  
    bool _assigned;

public:
    Variable(const std::string &name, Domain &domain, int variableId = -1); // The associated domain must be previously created

    static int getNbAssigned();
    static void setNbAssigned(int nb);

    void addConstraint(Constraint *constraint);
    
    Domain &getDomain();
    std::string const &getName() const;
    std::vector <Constraint *> const &getInvolvedConstraints() const;
    
    int getId();
    void setId(int id);
    bool isAssigned() const;
    void setAssigned(bool a);

    bool hasEmptyDomain() const;

    friend std::ostream& operator<<(std::ostream &flux, const Variable &variable);
};

#endif
