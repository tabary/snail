#include "ForwardChecking.h"

using namespace std;

ForwardChecking::ForwardChecking(Problem &problem) : Propagator(problem)
{  
}

bool ForwardChecking::propagate(int variableIndex, int valueIndex, int depth)
{
  variableValue v;
    vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();
    
    for (int i = 0 ; i < (int) constraints.size() ; ++i ) {     
        vector<Variable *>  const &scope = constraints[i]->getScope();
        tuple &t = constraints[i]->getMyTuple();
        
        // Init of the tuple
        for (int l=0; l < (int) scope.size(); ++l) {
            if (scope[l]->getId() == variableIndex)
                t[l] = scope[l]->getDomain().getValueOfIndex(valueIndex);
            else
                t[l] = -1;    
        }
        
        for (int j = 0 ; j < (int) scope.size() ; ++j) {            
            int index = scope[j]->getId();
            if (index == variableIndex || scope[j]->isAssigned())  
                continue;
            std::vector<int> const &currentDomain = scope[j]->getDomain().getCurrentDomain() ;
            for (int k = 0; k < (int) currentDomain.size(); ++k){
                if (currentDomain[k] == -1){
                    t[j] = scope[j]->getDomain().getValueOfIndex(k);  
                    if (!constraints[i]->isConsistent(t)){
                        v.variableIndex = index ;
                        v.valueIndex = k;
                        v.depth = depth ;
                        propagationStack.push(v);
                        scope[j]->getDomain().removeIndexAtDepth(k,depth);
                       
#ifdef TRACE  
                        cout << "Propagation at depth " << depth  << " of variableIndex :" << v.variableIndex << " with valueIndex " << v.valueIndex <<  endl;
#endif
                        
                    }
                }
            }
            t[j]=-1;
            if (scope[j]->hasEmptyDomain())
                return false;
        }
    }
    return true;
}


void ForwardChecking::undoPropagation(int depth)
{
       variableValue v;
    while (!propagationStack.empty()) {
        v = propagationStack.top();
        if (v.depth < depth)
            break;
        propagationStack.pop();
        
#ifdef TRACE  
           cout << "Undo Propagation at depth " << depth  << " of variableIndex :" << v.variableIndex << " with value " << v.valueIndex <<  endl;
#endif
        _problem.getVariable(v.variableIndex).getDomain().restoreUniqueIndexAtDepth(v.valueIndex,v.depth);
    } 
    
}