#include "Problem.h"

using namespace std;

Problem::Problem () { }

void
Problem::consolidate ()
{
  for(int i=0;i< (int) _variablesCollection.size (); ++i){
      _variablesCollection[i]->setIndex (i);
    }
  for(int i=0;i< (int) _constraintsCollection.size (); ++i){
      _constraintsCollection[i]->consolidate (i);
      if (_constraintsCollection.size () == 0 || minArity > _constraintsCollection[i]->getArity ())
        minArity = _constraintsCollection[i]->getArity ();
      if (_constraintsCollection.size () == 0 || maxArity < _constraintsCollection[i]->getArity ())
        maxArity = _constraintsCollection[i]->getArity ();      
    }
  
  cout << "Problem is consolidated" << endl;
}



void
Problem::setName (const string &name)
{
  _name = name;
}

void
Problem::addVariable (Variable *variable)
{
  _variablesCollection.push_back (variable);
}

void
Problem::addConstraint (Constraint *constraint)
{
  _constraintsCollection.push_back (constraint);
}

vector <Constraint *> const &
Problem::getConstraintsCollection () const
{
  return _constraintsCollection;
}

vector <Variable *> &
Problem::getVariablesCollection ()
{
  return _variablesCollection;
}

Variable &
Problem::getVariable (int variableIndex) const
{
  return *(_variablesCollection[variableIndex]);
}

int
Problem::getNbVariables () const
{
  return _variablesCollection.size ();
}

int
Problem::getNbConstraints () const
{
  return _constraintsCollection.size ();
}

int
Problem::getMinArity ()
{
  return minArity;
}

int
Problem::getMaxArity ()
{
  return maxArity;
}

void
Problem::display () const
{
  cout << "************** DISPLAY PROBLEM " << _name << " ************" << endl;
  for (unsigned int i = 0; i < _variablesCollection.size (); ++i)
    {
      cout << *(_variablesCollection[i]) << endl;
    }
  for (unsigned int i = 0; i < _constraintsCollection.size (); ++i)
    {
      cout << *(_constraintsCollection[i]) << endl;
    }
}




