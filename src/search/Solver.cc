#include "Solver.hh"

using namespace std;

Solver::Solver (Problem &problem) : _problem (problem), _nbFoundSolutions (0)
{
  //_propagator = new BinaryForwardChecking (_problem.getNbConstraints ());
_propagator = new BinaryAC3 (_problem.getNbConstraints ());
  vector<Constraint *> const &constraints = _problem.getConstraintsCollection();
    for(size_t i(0); i<  constraints.size (); ++i)
       _propagator->dealWith(constraints[i]);
      
  _variableHeuristic = new Dom(problem.getVariablesCollection());
  //_variableHeuristic = new Lexico(problem.getVariablesCollection());
}

void
Solver::doAssignmentAtCurrentDepth (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
  Variable &v = _problem.getVariable (variableIndex);
#ifdef TRACE  
  cout << v.getName () << " = " << v.getDomain ().getValueOfIndex (valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain ().reduceToIndexAtDepth (valueIndex, depth);
  v.setAssigned (true);
}

void
Solver::undoAssignment (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
  Variable &v = _problem.getVariable (variableIndex);
#ifdef TRACE
  cout << "undo assignement of " << v.getName () << " = " << v.getDomain ().getValueOfIndex (valueIndex) << endl;
#endif
 
  _propagator->undoPropagation (depth);
 
  v.getDomain ().restoreAllIndexAtDepth (depth);
  v.setAssigned (false);
}

void
Solver::tryRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
  Variable &v = _problem.getVariable (variableIndex);
#ifdef TRACE
  cout << v.getName () << " != " << v.getDomain ().getValueOfIndex (valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain ().removeIndexAtDepth (valueIndex, depth);
}

void
Solver::undoRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
  Variable &v = _problem.getVariable (variableIndex);

#ifdef TRACE  
  cout << "undo refutation of " << v.getName () << " != " << v.getDomain ().getValueOfIndex (valueIndex) << " at depth " << depth << endl;
#endif
  v.getDomain ().restoreUniqueIndexAtDepth (valueIndex, depth);
}

//bool
//Solver::checkConsistency (int variableIndex, int valueIndex, int depth)
//{
//  //    vector<Constraint *> const &constraints = _problem.getConstraintsCollection();
//  vector<Constraint *> const &constraints = _problem.getVariable (variableIndex).getInvolvedConstraints ();
//  // Check only the consistency where variableIndex is involved
//  for (unsigned int i = 0; i < constraints.size (); ++i)
//    {
//      if (!constraints[i]->isConsistent ())
//        return false;
//    }
//  return true;
//}

bool
Solver::checkConsistencyAfterAssignement (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
 return _propagator->propagate ({&(_problem.getVariable (variableIndex))}, valueIndex, depth);
 //return checkConsistency(variableIndex,valueIndex,depth);
 
}

bool
Solver::checkConsistencyAfterRefutation (unsigned int variableIndex, unsigned int valueIndex, unsigned int depth)
{
  return (!_problem.getVariable(variableIndex).hasEmptyDomain ());
}

void
Solver::doSearch ()
{
  cout << "************** BEGIN SEARCH ************" << endl;
  
  
   unsigned int depth (0);

  unsigned int variableIndex;
  unsigned int valueIndex;

  decision d;

  bool fullExploration (false);
  bool stop;

  Variable::setNbAssigned (0);

  if (_propagator->initialize ()==false)
    fullExploration=true;
  
  while (!fullExploration)
    {
      
      variableIndex = _variableHeuristic->chooseVariable ().getIndex ();   
      valueIndex = _problem.getVariable (variableIndex).getDomain ().getFirstPresentIndex ();

      doAssignmentAtCurrentDepth (variableIndex, valueIndex, depth++);

      d.polarity = true; // Should be in the doAssignment procedure ?????
      d.variableIndex = variableIndex;
      d.valueIndex = valueIndex;
      decisionStack.push (d);

      if (checkConsistencyAfterAssignement (variableIndex, valueIndex, depth - 1))
        {
          if (Variable::getNbAssigned () < _problem.getNbVariables ())
            continue;
          assert (Variable::getNbAssigned () == _problem.getNbVariables ());
          if (DealWithNewSolution (decisionStack))
            break;
        }

      stop = false;
      do
        {

          depth--;

          d = decisionStack.top ();
          decisionStack.pop ();
          if (d.polarity == false)
            {
              undoRefutation (d.variableIndex, d.valueIndex, depth);
            }
          else
            {
              undoAssignment (d.variableIndex, d.valueIndex, depth);
              d.polarity = false;
              decisionStack.push (d);
              tryRefutation (d.variableIndex, d.valueIndex, depth++);
              if (checkConsistencyAfterRefutation (d.variableIndex, d.valueIndex, depth - 1)) stop = true;
            }
        }
      while (!stop && !decisionStack.empty ());
      if (decisionStack.empty ()) fullExploration = true;
    }

  cout << "************** END SEARCH ************" << endl;
  if (fullExploration)
    {
      cout << "Full exploration is done";
      if (_nbFoundSolutions == 0)
        cout << "No solution found";
      cout << endl;
    }
  else
    {
      if (_nbFoundSolutions == NB_MAX_SOLUTIONS)
         cout << "NB Max solutions (" << NB_MAX_SOLUTIONS << ") has been reached";
      else
            throw ("Unreachable Code");
      cout << endl;
    }
}

bool
Solver::DealWithNewSolution (std::stack<decision> solutionStack)
{
  assert (Variable::getNbAssigned () == _problem.getNbVariables ());
  decision myDecision;
  ++_nbFoundSolutions;
  cout << "Solution #" << _nbFoundSolutions << " : ";
  while (!solutionStack.empty ())
    {
      myDecision = solutionStack.top ();
      solutionStack.pop ();
      if (myDecision.polarity == true)
        {
          Variable &v = _problem.getVariable (myDecision.variableIndex);
          cout << v.getName () << " = " << v.getDomain ().getValueOfIndex (myDecision.valueIndex) << " ";
        }
    }
  cout << endl;
  if (_nbFoundSolutions == NB_MAX_SOLUTIONS)
    return true;
  return false;
}


