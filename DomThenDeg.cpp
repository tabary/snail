#include "DomThenDeg.h"

using namespace std;

DomThenDeg::DomThenDeg(vector <Variable*> &variables) : VariableOrderingHeuristic(variables)
{  
}

int DomThenDeg::chooseVariable()
{
    int variableIndex = -1;
    int minDom= 0;
    int minDegree = 0;
    for (unsigned int i = 0; i < _variablesCollection.size(); ++i){
       if (_variablesCollection[i]->isAssigned())
            continue;
        if (variableIndex == -1 ||
           (_variablesCollection[i]->getDomain().getNbCurrentValues() < minDom) ||
           (_variablesCollection[i]->getDomain().getNbCurrentValues() == minDom && _variablesCollection[i]->getDegree() < minDegree )) {
            variableIndex = i;
            minDom=_variablesCollection[i]->getDomain().getNbCurrentValues();
            minDegree= _variablesCollection[i]->getDegree() ;
        }
    }    
    assert (variableIndex != -1);
    return variableIndex;
}