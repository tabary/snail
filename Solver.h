#ifndef DEF_SOLVER
#define DEF_SOLVER

#include "Problem.h"


class Solver
{
 private :
  Problem &d_problem; 

 public :
  Solver(Problem &problem);
 
  void doSearch();

};

#endif
