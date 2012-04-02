#include "Problem.h"

using namespace std;




Problem::Problem()
{
}
 
void Problem::addVariable(Variable *variable)
{
  d_variablesCollection.push_back(variable);
}

void Problem::addConstraint(Constraint *constraint)
{
  d_constraintsCollection.push_back(constraint);
}

vector <Constraint *> const &Problem::getConstraintsCollection() const
{
  return d_constraintsCollection;
}



Variable &Problem::getVariable(int variableIndex)
{
  return *(d_variablesCollection[variableIndex]);
}

int Problem::getNbVariables()
{
  return d_variablesCollection.size();
}


int Problem::getFirstUnassignedVariable()
{
 for(unsigned int i=0; i < d_variablesCollection.size(); i++)
   if (!d_variablesCollection[i]->isAssigned())
     return i;
   assert(false);
   return -1;
}

void Problem::display()
{
  cout << "************** DISPLAY PROBLEM ************" << endl;
  for(unsigned int i=0; i < d_variablesCollection.size(); i++){
    cout << *(d_variablesCollection[i]) << endl;
  }
  for(unsigned int i=0; i < d_constraintsCollection.size(); i++){
    cout << *(d_constraintsCollection[i]) << endl;
  }
}




