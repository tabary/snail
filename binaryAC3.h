#ifndef DEF_BINARYAC3
#define DEF_BINARYAC3

#include "Propagator.h"
#include "list"

/* For the moment the GAC3 class performs arc consisency with no optimizations
    See the definition of Mackworth77
 
    NON BINARY CONSTRAINTS ARE SKIPPED 

 */

class BinaryAC3 : public Propagator
{
  private:
    std::list<Variable*> propagationQueue;
    
    bool revise(Constraint& c,Variable& x, int depth);
    bool seekSupport(Constraint& c,Variable& x, int indexValue);
    
    public:
      BinaryAC3 (int nbConstraints);
      
      virtual bool propagate (Variable* variable, int valueIndex, int depth);
      virtual void undoPropagation (int depth);
      virtual bool initialize() ;
};

#endif
