#include "BinaryForwardChecking.h"

using namespace std;

BinaryForwardChecking::BinaryForwardChecking(Problem &problem) : Propagator(problem)
{  
    assert(problem.getMinArity() == 2 && problem.getMaxArity() == 2);
}

bool BinaryForwardChecking::propagate(int variableIndex, int valueIndex, int depth)
{
    variableValue v;
    vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();
    
    for (int i = 0 ; i < (int) constraints.size() ; ++i ) {      
        if (constraints[i]->getArity() != 2)
            continue;        
        vector<Variable *>  const &scope = constraints[i]->getScope();
        tuple &t = constraints[i]->getMyTuple();
        int positionOfFutureVariableInScope;
        
        // Init of the tuple with the assigned variable and determine the index of the second variable (unassigned variable)
        for (int j=0; j < (int) scope.size(); ++j) {
            if (scope[j]->getIndex() == variableIndex)
                t[j] = scope[j]->getDomain().getValueOfIndex(valueIndex);
            else {
                t[j] = -1; 
                positionOfFutureVariableInScope=j;
            }
        }
        
        std::vector<int> const &currentDomainOfFutureVariable = scope[positionOfFutureVariableInScope]->getDomain().getCurrentDomain() ;
        Variable* futureVariable = scope[positionOfFutureVariableInScope];
        
        for (int j = 0; j < (int) currentDomainOfFutureVariable.size(); ++j){
                if (currentDomainOfFutureVariable[j] == -1){
                    t[positionOfFutureVariableInScope] = futureVariable->getDomain().getValueOfIndex(j);  
                    if (!constraints[i]->isConsistent(t)){
                        v.variableIndex = futureVariable->getIndex();
                        v.valueIndex = j;
                        v.depth = depth ;
                        propagationStack.push(v);
                        futureVariable->getDomain().removeIndexAtDepth(j,depth);     
#ifdef TRACE  
                        cout << "Propagation at depth " << v.depth  << " of variableIndex :" << v.variableIndex << " with valueIndex " << v.valueIndex <<  endl;
#endif
                    }
                }
            }
        
        if (futureVariable->hasEmptyDomain())
                return false;  
    }
    return true;
}


void BinaryForwardChecking::undoPropagation(int depth)
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