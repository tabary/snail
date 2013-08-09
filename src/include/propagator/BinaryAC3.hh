#ifndef DEF_BINARYAC3
#define DEF_BINARYAC3


#include <cassert>
#include <list>
#include "Propagator.hh"

/* For the moment the GAC3 class performs arc consisency with no optimizations
    See the definition of Mackworth77
 */

class BinaryAC3 : public Propagator
{
private:
  std::list<Variable*> propagationQueue;

  bool revise (Constraint& c, Variable& x, unsigned int depth);
  //  bool seekSupport(Constraint& c,Variable& x, unsigned int indexValue);



  void printTuple (const snail::tuple &t, int arity);

public:
  BinaryAC3 (unsigned int nbConstraints);
  bool seekSupport (Constraint& c, Variable& x, unsigned int indexValue);
  virtual bool propagate (Variable* variable, unsigned int valueIndex, unsigned int depth);
  virtual void undoPropagation (unsigned int depth);
  virtual bool initialize ();
};

#endif
