#ifndef DEF_SOLVER
#define DEF_SOLVER

#include "Problem.h"


class Solver
{
 private :
  Problem &d_problem; 

 typedef struct {
    int variableIndex; // in the variablesCollection vector of Problem class
    int valueIndex; // index of the value in the domain 
    bool polarity; // true = assignement and false = refutation
  } decision;

 std::vector<decision> decisionStack;


 void doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth);


 public :
 Solver(Problem &problem);
 
  void doSearch();

};

#endif
