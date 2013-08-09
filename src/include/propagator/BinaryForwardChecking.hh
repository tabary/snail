#ifndef DEF_BINARYFORWARDCHECKING
#define DEF_BINARYFORMARDCHECKING

#include <cassert>

#include "Propagator.hh"

/* For the moment the forwardChecking class deals only with binary constraints  
    See the definition of Haralick and Elliot HE80 
 
    NON BINARY CONSTRAINTS ARE ASSERTED

 */


class BinaryForwardChecking : public Propagator
{
public:

  BinaryForwardChecking (unsigned int nbConstraints);
  
  virtual bool propagate (Variable* variable, unsigned int valueIndex, unsigned int depth);
  virtual void undoPropagation (unsigned int depth);
  virtual bool initialize();
};

#endif
