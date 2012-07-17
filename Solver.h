#ifndef DEF_SOLVER
#define DEF_SOLVER

#include "Problem.h"
#include "VariableOrderingHeuristic.h"
#include "stack"


#define NB_MAX_SOLUTIONS 50000


class Solver
{
 private :
  Problem &_problem; 
  VariableOrderingHeuristic * _variableHeuristic;

  typedef struct {
    int variableIndex; // in the variablesCollection vector of Problem class
    int valueIndex; // index of the value in the domain 
    bool polarity; // true = assignement and false = refutation
  } decision;
  std::stack<decision> decisionStack;
  
  typedef struct {
      int variableIndex;
      int valueIndex;
      int depth;
  }variableValue;
  std::stack<variableValue> propagationStack;
  
  int _nbFoundSolutions;
  
  bool DealWithNewSolution( std::stack<decision> solutionStack); // true : NB_MAX_SOLUTIONS is reached

  void doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth);
  void undoAssignment(int variableIndex, int valueIndex, int depth);
  
  void tryRefutation(int variableIndex, int valueIndex, int depth);
  void undoRefutation(int variableIndex, int valueIndex, int depth);
  
  void undoPropagation(int depth) ;

  bool checkConsistency(int variableIndex, int valueIndex, int depth) ;
  bool checkForward(int variableIndex, int valueIndex, int depth)  ;
  
  bool checkConsistencyAfterAssignement(int variableIndex, int valueIndex, int depth) ;
  bool checkConsistencyAfterRefutation(int variableIndex, int valueIndex, int depth) ;
  
 public :
  Solver(Problem &problem);
 
  void doSearch();

};

#endif
