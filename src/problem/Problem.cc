#include "Problem.hh"

using namespace std;

Problem::Problem () { }

bool
Problem::consolidateVariables ()
{
  for (size_t i(0); i < _variablesCollection.size(); ++i){
    if (_variablesCollection[i] == NULL || _variablesCollection[i]->getIndex () != i)
      return false;
  }
  return true;
}

bool
Problem::consolidateConstraints ()
{
  for (size_t i(0); i < _constraintsCollection.size(); ++i){
    if (_constraintsCollection[i] == NULL || _constraintsCollection[i]->getIndex () != i)
      return false;
    std::vector <Variable *> const &scope = _constraintsCollection[i]->getScope ();
    for (size_t j(0); j < scope.size(); ++j)
      scope[j]->addConstraint (_constraintsCollection[i]);
    if (i == 0 || minArity > _constraintsCollection[i]->getArity ())
        minArity = _constraintsCollection[i]->getArity ();
      if (i == 0 || maxArity < _constraintsCollection[i]->getArity ())
        maxArity = _constraintsCollection[i]->getArity ();      
    }
  return true;
}

void
Problem::setName (const string &name)
{
  _name = name;
}

void
Problem::addVariableAtIndex (Variable *variable,int index)
{
  assert(_variablesCollection[index]==NULL);
  _variablesCollection[index] = variable;
}

void
Problem::initVariables (int nbVariables)
{
  assert(nbVariables >0);
  _variablesCollection.resize (nbVariables,NULL);
}

void
Problem::addConstraintAtIndex (Constraint *constraint, int index)
{
  assert(_constraintsCollection[index]==NULL);
  _constraintsCollection[index] = constraint;
}

void
Problem::initConstraints (int nbConstraints)
{
  assert(nbConstraints >0);
  _constraintsCollection.resize (nbConstraints,NULL);
}



Variable &
Problem::getVariable (int variableIndex) const
{
  return *(_variablesCollection[variableIndex]);
}

vector <Constraint *> const &
Problem::getConstraintsCollection () const
{
  return _constraintsCollection;
}

vector <Variable *> const &
Problem::getVariablesCollection () const
{
  return _variablesCollection;
}

unsigned int
Problem::getNbVariables () const
{
  return _variablesCollection.size ();
}

unsigned int
Problem::getNbConstraints () const
{
  return _constraintsCollection.size ();
}

unsigned int
Problem::getMinArity () const
{
  return minArity;
}

unsigned int
Problem::getMaxArity () const
{
  return maxArity;
}

void
Problem::display () const
{
  cout << "************** DISPLAY PROBLEM " << _name << " ************" << endl;
  for (size_t i = 0; i < _variablesCollection.size (); ++i)
          cout << *(_variablesCollection[i]) << endl;
  
  for (size_t  i = 0; i < _constraintsCollection.size (); ++i)
    {
      cout << *(_constraintsCollection[i]) << endl;
    }
}




