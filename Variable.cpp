#include "Variable.h"

using namespace std;

int Variable::nbAssigned = 0;

Variable::Variable(const string &name, Domain &domain, int variableId) : _name(name), _Id(variableId), _domain(domain), _assigned(false) {
}

int Variable::getNbAssigned() {
    return nbAssigned;
}

void Variable::setNbAssigned(int nb) {
    nbAssigned = nb;
}

void Variable::addConstraint(Constraint *constraint) {
    _involvedConstraints.push_back(constraint);
}

Domain &Variable::getDomain() const {
    return _domain;
}

string const &Variable::getName() const {
    return _name;
}

std::vector <Constraint *> const &Variable::getInvolvedConstraints() const {
    return _involvedConstraints;
}

int Variable::getId() const {
    return _Id;
}

void Variable::setId(int id) {
    _Id = id;
}

bool Variable::isAssigned() const {
    return _assigned;
}

void Variable::setAssigned(bool a) {
    assert(_assigned != a);
    _assigned = a;
    if (a == true)
        nbAssigned++;
    else
        nbAssigned--;
}

bool Variable::hasEmptyDomain() const {
    return (_domain.getNbRemovals() == _domain.getNbInitialValues());
}

ostream& operator<<(ostream &flux, const Variable &variable) {
    flux << variable._name << " with associated domain " << variable._domain;
    return flux;
}
