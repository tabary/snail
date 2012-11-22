#include "DomOnDDeg.h"

using namespace std;

DomOnDDeg::DomOnDDeg(vector <Variable*> &variables) : VariableOrderingHeuristic(variables)
{  
}

int DomOnDDeg::chooseVariable()
{
    int variableIndex = -1;
    float cost = 0;
    for (unsigned int i = 0; i < _variablesCollection.size(); ++i){
        if (_variablesCollection[i]->isAssigned())
            continue;
        if (variableIndex == -1 || (_variablesCollection[i]->getDomain().getNbCurrentValues()/ _variablesCollection[i]->getDDegree() ) < cost ) {
            variableIndex = i;
            cost = _variablesCollection[i]->getDomain().getNbCurrentValues()/ _variablesCollection[i]->getDDegree() ;
        }
    }    
    assert (variableIndex != -1);
    return variableIndex;
}