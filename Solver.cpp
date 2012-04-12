#include "Solver.h"

using namespace std;




Solver::Solver(Problem &problem) : d_problem(problem)
{
}
 
bool Solver::checkConsistency()
{
  vector<Constraint *> const &constraints = d_problem.getConstraintsCollection();
  for(int i=0; i< (int)constraints.size(); i++){
    if (!constraints[i]->isConsistent())
      return false;
  }
  return true;
}



void Solver::doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TRACE  
  cout << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain().reduceToIndexAtDepth(valueIndex,depth);
  v.setAssigned(true);
}



void Solver::undoAssignment(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TRACE
  cout << "undo assignement of " << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << endl;
#endif
  v.getDomain().restoreAllIndexAtDepth(depth); 
  v.setAssigned(false);
}


void Solver::undoRefutation(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TRACE  
  cout << "undo refutation of " << v.getName() << " != " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain().restoreUniqueIndexAtDepth(valueIndex, depth); 
}


void Solver::tryRefutation(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TRACE
  cout << v.getName() << " != " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain().removeIndex(valueIndex, depth); 
}


void Solver::backtrack(int &depth)
{
  decision d;
  bool stop(false);

  do {
    d = decisionStack.top();
    decisionStack.pop();
      
    if (d.polarity == false){
      undoRefutation(d.variableIndex,d.valueIndex,depth--);
    }
    else{
      undoAssignment(d.variableIndex,d.valueIndex,depth--);
      d.polarity = false;
      decisionStack.push(d);
      tryRefutation(d.variableIndex,d.valueIndex,++depth);
      if (checkConsistency()) stop = true;
    }
  }
  while (!stop && !decisionStack.empty());
}


void Solver::doSearch()
{
  cout << "************** BEGIN SEARCH ************" << endl;

  int depth(0);

  int variableIndex(0);
  int valueIndex(0);

  decision d;

  bool fullExploration(false);
  
  while(!fullExploration && Variable::getNbAssigned() < d_problem.getNbVariables()){
 
    variableIndex = d_problem.getFirstUnassignedVariable();
    valueIndex= d_problem.getVariable(variableIndex).getDomain().getFirstPresentIndex();
    doAssignmentAtCurrentDepth(variableIndex,valueIndex,++depth);

    d.polarity = true;
    d.variableIndex = variableIndex;
    d.valueIndex = valueIndex;
    decisionStack.push(d);

    if (checkConsistency()) continue;
    
    backtrack(depth);

    if (decisionStack.empty()) fullExploration=true;
  }
  
  cout << "************** END SEARCH ************" << endl;



  if (Variable::getNbAssigned() == d_problem.getNbVariables()){
    cout << "Solution Found : " << endl;
    while (!decisionStack.empty())
      {
	d = decisionStack.top();
	decisionStack.pop();
	if (d.polarity == true){
	  Variable &v = d_problem.getVariable(d.variableIndex);
	  cout << v.getName() << " = " << v.getDomain().getValueOfIndex(d.valueIndex) << " " ;
	}
      }
  }
  else{
    cout << "No solution found, full exploration done" ;
  }
}





