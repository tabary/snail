#ifndef DEF_SOLVER
#define DEF_SOLVER

#include "Problem.h"
#include "stack"



#define NB_MAX_SOLUTIONS 1


class Solver
{
 private :
  Problem &_problem; 

  typedef struct {
    int variableIndex; // in the variablesCollection vector of Problem class
    int valueIndex; // index of the value in the domain 
    bool polarity; // true = assignement and false = refutation
  } decision;

  std::stack<decision> decisionStack;
  int _nbFoundSolutions;
  
  bool DealWithNewSolution( std::stack<decision> solutionStack); // true : NB_MAX_SOLUTIONS is reached

  void doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth);
  void undoAssignment(int variableIndex, int valueIndex, int depth);
  void undoRefutation(int variableIndex, int valueIndex, int depth);
  void tryRefutation(int variableIndex, int valueIndex, int depth);

 public :
  Solver(Problem &problem);

  bool checkConsistency() const;
  void doSearch();

};

#endif
