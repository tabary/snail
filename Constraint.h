#ifndef DEF_CONSTRAINT
#define DEF_CONSTRAINT

#include "Relation.h"
#include "Variable.h"

class Constraint {
private:
    std::string _name;
    int _arity;
    Variable **_scope;
    Relation const &_relation;

public:
    Constraint(const std::string &name, int arity, Variable **scope, Relation const &relation); // The associated domain must be previously created

    bool isConsistent() const;

    friend std::ostream& operator<<(std::ostream &flux, const Constraint &constraint);
};

#endif
