#include "Problem.h"

#include <iostream>

using namespace std;

int main()
{

  cout << "Hello from SnaiL \n";


  Problem p;


  Domain d0("D0", 1, 2);
  Domain d1("D1", 0, 26);
  Domain d2("D2", 24, 25);

  Variable v0("V0", *(new Domain(d0)));
  Variable v1("V1", *(new Domain(d1)));
  Variable v2("V2", *(new Domain(d1)));
  Variable v3("V3", *(new Domain(d1)));
  Variable v4("V4", *(new Domain(d1)));
  Variable v5("V5", *(new Domain(d2)));

  p.addVariable(&v0);
  p.addVariable(&v1);
  p.addVariable(&v2);
  p.addVariable(&v3);
  p.addVariable(&v4);

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

  Variable** scp= new Variable*[2];
  scp[0]=&v0; scp[1]=&v1; Constraint c0("C0", 2, scp, r0);
  scp[0]=&v1; scp[1]=&v2; Constraint c1("C1", 2, scp, r0); // TODO Modify relation r1 for constraint
  scp[0]=&v2; scp[1]=&v3; Constraint c2("C2", 2, scp, r0); // TODO Modify relation r1 for constraint
  scp[0]=&v3; scp[1]=&v4; Constraint c3("C3", 2, scp, r0); // TODO Modify relation r1 for constraint
  scp[0]=&v4; scp[1]=&v5; Constraint c4("C4", 2, scp, r2);

  p.addConstraint(&c0);
  p.addConstraint(&c1);
  p.addConstraint(&c2);
  p.addConstraint(&c3);
  p.addConstraint(&c4);
  
  p.display();

  return 0;
}
