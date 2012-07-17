#ifndef DEF_CONSTRAINT
#define DEF_CONSTRAINT

#include "Relation.h"
#include "Variable.h"

class Variable;


class Constraint {
private:
    std::string _name;
    int _arity;

    std::vector <Variable *> _scope;    
    Relation const &_relation;
    
    tuple myTuple; // temporary tuple

public:
    Constraint(const std::string &name, int arity, Relation const &relation); // The associated domain must be previously created

    bool isConsistent() const;
    bool isConsistent(tuple t);

    std::vector <Variable *>  const &getScope() const;
    
    int getArity();
    
    void addVariableToScope(Variable *variable);
    
    tuple &getMyTuple();

    friend std::ostream& operator<<(std::ostream &flux, const Constraint &constraint);
};

#endif
