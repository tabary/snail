#include "Solver.h"

using namespace std;

Solver::Solver(Problem &problem) : _problem(problem), _nbFoundSolutions(0) {
}

bool Solver::checkConsistency(int variableIndex, int valueIndex, int depth)  {
    //    vector<Constraint *> const &constraints = _problem.getConstraintsCollection();
    vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();
    // Check only the consistency where variableIndex is involved
    for (int i = 0; i < (int) constraints.size(); ++i) {
        if (!constraints[i]->isConsistent())
            return false;
    }
    
  
   
    return true;
}

 // TODO
bool Solver::checkForward(int variableIndex, int valueIndex, int depth)  {
         variableValue v;
vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();

for (int i = 0 ; i < (int) constraints.size() ; ++i ) {
    
    vector<Variable *>  &scope = constraints[i]->getScope();
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
        if (scope[j]->getDomain().getNbRemovals() == scope[j]->getDomain().getNbInitialValues())
            return false;
    }
}
return true;
}

    



void Solver::doAssignmentAtCurrentDepth(int variableIndex, int valueIndex, int depth) {
    Variable &v = _problem.getVariable(variableIndex);
#ifdef TRACE  
    cout << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
    v.getDomain().reduceToIndexAtDepth(valueIndex, depth);
    v.setAssigned(true);
}

void Solver::undoAssignment(int variableIndex, int valueIndex, int depth) {
    Variable &v = _problem.getVariable(variableIndex);
#ifdef TRACE
    cout << "undo assignement of " << v.getName() << " = " << v.getDomain().getValueOfIndex(valueIndex) << endl;
#endif
      undoPropagation(depth);
    v.getDomain().restoreAllIndexAtDepth(depth);
    v.setAssigned(false);
}

void Solver::undoRefutation(int variableIndex, int valueIndex, int depth) {
    Variable &v = _problem.getVariable(variableIndex);
   
#ifdef TRACE  
    cout << "undo refutation of " << v.getName() << " != " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
    v.getDomain().restoreUniqueIndexAtDepth(valueIndex, depth);
}

void Solver::tryRefutation(int variableIndex, int valueIndex, int depth) {
    Variable &v = _problem.getVariable(variableIndex);
#ifdef TRACE
    cout << v.getName() << " != " << v.getDomain().getValueOfIndex(valueIndex) << " at depth " << depth << endl;
#endif
    v.getDomain().removeIndexAtDepth(valueIndex, depth);
}

bool Solver::DealWithNewSolution(std::stack<decision> solutionStack){
       assert(Variable::getNbAssigned() == _problem.getNbVariables());
       decision myDecision;
       ++_nbFoundSolutions;
       cout << "Solution #" << _nbFoundSolutions << " : " ;
       while (!solutionStack.empty()) {
           myDecision = solutionStack.top();
           solutionStack.pop();
           if (myDecision.polarity == true) {
               Variable &v = _problem.getVariable(myDecision.variableIndex);
               cout << v.getName() << " = " << v.getDomain().getValueOfIndex(myDecision.valueIndex) << " ";
           }
       }
       cout << endl;
        if (_nbFoundSolutions == NB_MAX_SOLUTIONS)
            return true;
       return false;
}




void Solver::undoPropagation(int depth) {
         
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






bool Solver::checkConsistencyAfterAssignement(int variableIndex, int valueIndex, int depth) {
    
    if (!checkConsistency(variableIndex,valueIndex,depth))
        return false;
    return checkForward(variableIndex,valueIndex,depth);
   
}





bool Solver::checkConsistencyAfterRefutation(int variableIndex, int valueIndex, int depth) {
    
    return checkConsistency(variableIndex,valueIndex,depth);
    
}









void Solver::doSearch() {
    cout << "************** BEGIN SEARCH ************" << endl;

    int depth(0);

    int variableIndex(0);
    int valueIndex(0);

    decision d;

    bool fullExploration(false);
    bool stop;

    Variable::setNbAssigned(0);

    while (!fullExploration) {
        variableIndex = _problem.getFirstUnassignedVariable();
        valueIndex = _problem.getVariable(variableIndex).getDomain().getFirstPresent();
        doAssignmentAtCurrentDepth(variableIndex, valueIndex, depth++);

        d.polarity = true;
        d.variableIndex = variableIndex;
        d.valueIndex = valueIndex;
        decisionStack.push(d);
        
        if (checkConsistencyAfterAssignement(variableIndex,valueIndex,depth-1)) {
            if (Variable::getNbAssigned() < _problem.getNbVariables())
                continue;
            assert(Variable::getNbAssigned() == _problem.getNbVariables());
            if(DealWithNewSolution(decisionStack))
                break;    
        }
        
        stop = false;
        do {
            
            depth--;
          
            
            d = decisionStack.top();
            decisionStack.pop();
            if (d.polarity == false) {
                undoRefutation(d.variableIndex, d.valueIndex, depth);
            } else {
                undoAssignment(d.variableIndex, d.valueIndex, depth);
                d.polarity = false;
                decisionStack.push(d);
                tryRefutation(d.variableIndex, d.valueIndex, depth++);
                if (checkConsistencyAfterRefutation(d.variableIndex,d.valueIndex,depth-1)) stop = true;
            }
        } while (!stop && !decisionStack.empty());
        if (decisionStack.empty()) fullExploration = true;
    }
     
    cout << "************** END SEARCH ************" << endl;
    if (fullExploration) {
        cout << "Full exploration is done";
        if (_nbFoundSolutions == 0)
        cout << "No solution found"; 
        cout << endl;
    }
   }





