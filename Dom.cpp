#include "Dom.h"

using namespace std;

Dom::Dom(vector <Variable*> &variables) : VariableOrderingHeuristic(variables)
{  
}

int Dom::selectVariable()
{
    int variableIndex = -1;
    for (unsigned int i = 0; i < _variablesCollection.size(); ++i){
        if (_variablesCollection[i]->isAssigned())
            continue;
        if (variableIndex == -1 || _variablesCollection[i]->getDomain().getNbCurrentValues() < _variablesCollection[variableIndex]->getDomain().getNbCurrentValues() )
            variableIndex = i;
    }    
    assert (variableIndex != -1);
    return variableIndex;
}