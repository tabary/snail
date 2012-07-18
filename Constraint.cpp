#include "Constraint.h"

using namespace std;


Constraint::Constraint(const string &name, int arity, Relation const &relation) : _name(name), _arity(arity), _nbUnassignedVariable(arity),  _relation(relation)
{
    assert(_arity >= 1);
    myTuple = new int[_arity];
} 

bool Constraint::isConsistent() const
{
    for(int i=0; i<_arity; ++i){
        if (_scope[i]->hasEmptyDomain())
            return false;
        if (!_scope[i]->isAssigned())
            return true;
        myTuple[i] = (_scope[i]->getDomain()).getUniquePresent(); 
    }
    if (_relation.isValid(myTuple))
        return true;
    return false;
}

bool Constraint::isConsistent(tuple t)
{
    return _relation.isValid(t);
}

bool Constraint::isCovered() const {
       return (_nbUnassignedVariable == 0 ? true : false);
}

void Constraint::incNbUnassignedVariable(){
    _nbUnassignedVariable++;
}

void Constraint::decNbUnassignedVariable(){
    _nbUnassignedVariable--;        
}

std::vector <Variable *> const &Constraint::getScope() const
{
    return _scope;    
}

int Constraint::getArity()
{
    return _arity;    
}

void Constraint::addVariableToScope(Variable *variable)
{
    _scope.push_back(variable);
}

tuple &Constraint::getMyTuple()
{
    return myTuple;
}

ostream& operator<<(ostream &flux, const Constraint &constraint)
{ 
    flux << constraint._name << " [";
    for (int i=0; i< constraint._arity; i++){
        flux << constraint._scope[i]->getName() << (i<constraint._arity-1 ? "," : "" ) ;
    }
    flux << "] with associated relation " << constraint._relation ;
    return flux;
}
