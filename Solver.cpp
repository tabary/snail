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
#ifdef TMPDEBUG  
  cout << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain().reduceToIndexAtDepth(valueIndex,depth);
  v.setAssigned(true);
}



void Solver::undoAssignment(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TMPDEBUG  
  cout << "undo assignement of " << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << endl;
#endif
  v.getDomain().restoreAllIndexAtDepth(depth); 
  v.setAssigned(false);
}

void Solver::tryRefutation(int variableIndex, int valueIndex, int depth)
{
  Variable &v = d_problem.getVariable(variableIndex);
#ifdef TMPDEBUG  
  cout << v.getName() << " != " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << endl;
#endif
  v.getDomain().removeIndex(valueIndex, depth); 
}

void Solver::doSearch()
{
  cout << "************** BEGIN SEARCH ************" << endl;

  bool fullExploration(false);
  
  int depth(0);

  int variableIndex(0);
  int valueIndex(0);

  decision d;

  while(!fullExploration){
    variableIndex = d_problem.getFirstUnassignedVariable();
    valueIndex= d_problem.getVariable(variableIndex).getDomain().getFirstPresentIndex();
    doAssignmentAtCurrentDepth(variableIndex,valueIndex,depth++);

    d.polarity = true;
    d.variableIndex = variableIndex;
    d.valueIndex = valueIndex;
    decisionStack.push(d);

    if (checkConsistency()) continue;
    depth--;
    undoAssignment(variableIndex,valueIndex,depth);
    decisionStack.pop();
    tryRefutation(variableIndex,valueIndex,depth++);

    d.polarity = false;
    d.variableIndex = variableIndex;
    d.valueIndex = valueIndex;
    decisionStack.push(d);

    if (checkConsistency()) continue;
    // Backtrack(); TODO

    // do
    // t = statck.pop()
    //   if t.polarity == false
    //       undoRefutation
    // 	     continue to depile
    // 	else
    // 	  undoAssignment
    // 	  tryRefutation
    // 	  if consistent then stop
    // 	    else continue to depile
    // 		   while (!stop et !enhaut de l'arbre)

  }
  cout << "************** END SEARCH ************" << endl;
}





