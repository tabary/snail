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

void Problem::display()
{
  cout << "************** DISPLAY PROBLEM ************" << endl;
  for(int i=0; i < d_variablesCollection.size(); i++){
    cout << *(d_variablesCollection[i]) << endl;
  }
  for(int i=0; i < d_constraintsCollection.size(); i++){
    cout << *(d_constraintsCollection[i]) << endl;
  }


}




