#ifndef DEF_SOLVER
#define DEF_SOLVER

#include "Problem.h"
#include "stack"

class Solver
{
 private :
  Problem &d_problem; 

  typedef struct {
    int variableIndex; // in the variablesCollection vector of Problem class
    int valueIndex; // index of the value in the domain 
    bool polarity; // true = assignement and false = refutation
  } decision;

  std::stack<decision> decisionStack;


  void doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth);
  void undoAssignment(int variableIndex, int valueIndex, int depth);
  void tryRefutation(int variableIndex, int valueIndex, int depth);

 public :
  Solver(Problem &problem);

  bool checkConsistency();
  void doSearch();

};

#endif
