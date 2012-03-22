#include "Solver.h"

using namespace std;




Solver::Solver(Problem &problem) : d_problem(problem)
{
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



void Solver::doSearch()
{
  cout << "************** BEGIN SEARCH ************" << endl;

  bool fullExploration(false);
  
  int depth(0);

  int variableIndex(0);
  int valueIndex(0);
  while(!fullExploration){
    variableIndex = d_problem.getFirstUnassignedVariable();
    //   valueIndex= d_problem.getVariable(variableIndex).getDomain().getFirstIndex();
    depth++;
    doAssignmentAtCurrentDepth(variableIndex,valueIndex,depth);
  }
  cout << "************** END SEARCH ************" << endl;
}





