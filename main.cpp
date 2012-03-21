#include "Domain.h"
#include "Variable.h"
#include "Relation.h"

#include <iostream>

using namespace std;

int main()
{

  cout << "Hello from SnaiL \n";

  Domain d0("D0", 1, 2);
  Domain d1("D1", 0, 26);
  Domain d2("D2", 24, 25);

  cout << d0 << endl ;
  cout << d1 << endl ;
  cout << d2 << endl ;
  
  Variable v0("V0", *(new Domain(d0)));
  Variable v1("V1", *(new Domain(d1)));
  Variable v2("V2", *(new Domain(d1)));
  Variable v3("V3", *(new Domain(d1)));
  Variable v4("V4", *(new Domain(d1)));
  Variable v5("V5", *(new Domain(d2)));

  cout << v0 << endl ;
  cout << v1 << endl ;
  cout << v2 << endl ;
  cout << v3 << endl ;
  cout << v4 << endl ;
  cout << v5 << endl ;

  Relation r0("R0",2);
  tuple myTuple= new int[2];
  myTuple[0]=1; myTuple[1]=0; r0.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=2; r0.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=7; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=0; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=1; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=5; r0.addTuple(myTuple);

  // TODO Definition of r1 relation of Hanoi3 problem

  Relation r2("R2",2);
  myTuple[0]=19; myTuple[1]=25; r2.addTuple(myTuple);
  myTuple[0]=21; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=24; myTuple[1]=25; r2.addTuple(myTuple);
  myTuple[0]=25; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=25; r2.addTuple(myTuple);

  cout << r0 << endl;
  cout << r2 << endl;
  return 0;
}
