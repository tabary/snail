#include "Solver.h"

using namespace std;

Solver::Solver(Problem &problem) : _problem(problem), _nbFoundSolutions(0) {
}

bool Solver::checkConsistency(int variableIndex, int valueIndex, int depth) const {
    //    vector<Constraint *> const &constraints = _problem.getConstraintsCollection();
    vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();
    // Check only the consistency where variableIndex is involved
    for (int i = 0; i < (int) constraints.size(); ++i) {
        if (!constraints[i]->isConsistent())
            return false;
    }    
    // Propagate and then checkConsistency
//    vector<Constraint *> const &constraints =_problem.getVariable(variableIndex).getInvolvedConstraints();
//    int myArity;
//    Variable ** myScope;
//    for (int i = 0; i < constraints.size(); ++i)
//    {
//        myArity = constraints[i].getArity();
//        myScope = constraints[i].getScope();
//        for (int j=0; j< myArity ; ++j)
//        {
//          if (myScope[j].getIndex == variableIndex) 
//              continue;
//          
//        }      
//    }
    
    
  
    
    return true;
}

 // TODO
bool Solver::checkForward(int variableIndex, int valueIndex) {
//   
//vector<Constraint *> const &constraints = _problem.getVariable(variableIndex).getInvolvedConstraints();
//
//for (int i = 0 ; i < (int) constraints.size() ; ++i ) {
//    vector<Variable *>  &variables = constraints[i]->getScope();
//    int * t = new int[constraints[i]->getArity()];
//    for (int j = 0 ; j < (int) variables.size() ; ++j) {
//        int index = variables[i]->getId();
//        if (index == variableIndex)  
//            continue;
//          std::vector<int> const &currentDomain = variables[i]->getDomain().getCurrentDomain() ;
//          for (int k = 0; k < (int) currentDomain.size(); ++k){
//              if (currentDomain[k] == -1){
//              
//          
//              }
//          }
//    }
//}
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
        
        if (checkConsistency(variableIndex,valueIndex,depth)) {
            if (Variable::getNbAssigned() < _problem.getNbVariables())
                continue;
            assert(Variable::getNbAssigned() == _problem.getNbVariables());
            if(DealWithNewSolution(decisionStack))
                break;    
        }
        
        stop = false;
        do {
            
            d = decisionStack.top();
            decisionStack.pop();
            if (d.polarity == false) {
                depth--;
                undoRefutation(d.variableIndex, d.valueIndex, depth);
            } else {
                depth--;
                undoAssignment(d.variableIndex, d.valueIndex, depth);
                d.polarity = false;
                decisionStack.push(d);
                tryRefutation(d.variableIndex, d.valueIndex, depth++);
                if (checkConsistency(d.variableIndex,d.valueIndex,depth)) stop = true;
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





