#ifndef DEF_SOLVER
#define DEF_SOLVER


#include "VariableOrderingHeuristic.hh"
#include "Dom.hh"
//#include "DomOnDDeg.h"
//#include "DomOnDeg.h"
#include "Lexico.hh"

#include "Propagator.hh"
#include "BinaryForwardChecking.hh"
#include "binaryAC3.hh"

#include "stack"
#include <cassert>

#include "global.hh"
#include "Problem.hh"



class Solver
{
private:
  Problem &_problem;
  VariableOrderingHeuristic * _variableHeuristic;
  
  Propagator * _propagator;

  typedef struct
  {
    int variableIndex; // in the variablesCollection vector of Problem class
    int valueIndex; // index of the value in the domain 
    bool polarity; // true = assignement and false = refutation
  } decision;
  std::stack<decision> decisionStack; // which corresponds to the current branch

  unsigned int _nbFoundSolutions;

  bool DealWithNewSolution (std::stack<decision> solutionStack); // return true if NB_MAX_SOLUTIONS is reached, false otherwise

  void doAssignmentAtCurrentDepth (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);
  void undoAssignment (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);

  void tryRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);
  void undoRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);

  //bool checkConsistency (int variableIndex, int valueIndex, int depth);

  bool checkConsistencyAfterAssignement (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);
  bool checkConsistencyAfterRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth);

public:
  Solver (Problem &problem);

  void doSearch ();

};

#endif
