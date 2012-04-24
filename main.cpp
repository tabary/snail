#include "Solver.h"
#include "parser/MyParser.h"


using namespace std;

int main(int argc, char **argv)
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
  p.addVariable(&v5);

  Relation r0("R0",2);
 tuple myTuple= new int[2];
  myTuple[0]=1; myTuple[1]=0; r0.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=2; r0.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=7; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=0; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=1; r0.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=5; r0.addTuple(myTuple);

  Relation r1("R1",2);
  myTuple[0]=0; myTuple[1]=1; r1.addTuple(myTuple);
  myTuple[0]=0; myTuple[1]=2; r1.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=0; r1.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=2; r1.addTuple(myTuple);
  myTuple[0]=1; myTuple[1]=7; r1.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=0; r1.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=1; r1.addTuple(myTuple);
  myTuple[0]=2; myTuple[1]=5; r1.addTuple(myTuple);
  myTuple[0]=3; myTuple[1]=4; r1.addTuple(myTuple);
  myTuple[0]=3; myTuple[1]=5; r1.addTuple(myTuple);

  myTuple[0]=3; myTuple[1]=6; r1.addTuple(myTuple);
  myTuple[0]=4; myTuple[1]=3; r1.addTuple(myTuple);
  myTuple[0]=4; myTuple[1]=5; r1.addTuple(myTuple);
  myTuple[0]=4; myTuple[1]=22; r1.addTuple(myTuple);
  myTuple[0]=5; myTuple[1]=2; r1.addTuple(myTuple);
  myTuple[0]=5; myTuple[1]=3; r1.addTuple(myTuple);
  myTuple[0]=5; myTuple[1]=4; r1.addTuple(myTuple);
  myTuple[0]=6; myTuple[1]=3; r1.addTuple(myTuple);
  myTuple[0]=6; myTuple[1]=7; r1.addTuple(myTuple);
  myTuple[0]=6; myTuple[1]=8; r1.addTuple(myTuple);


  myTuple[0]=7; myTuple[1]=1; r1.addTuple(myTuple);
  myTuple[0]=7; myTuple[1]=6; r1.addTuple(myTuple);
  myTuple[0]=7; myTuple[1]=8; r1.addTuple(myTuple);
  myTuple[0]=8; myTuple[1]=6; r1.addTuple(myTuple);
  myTuple[0]=8; myTuple[1]=7; r1.addTuple(myTuple);
  myTuple[0]=8; myTuple[1]=17; r1.addTuple(myTuple);
  myTuple[0]=9; myTuple[1]=10; r1.addTuple(myTuple);
  myTuple[0]=9; myTuple[1]=11; r1.addTuple(myTuple);
  myTuple[0]=9; myTuple[1]=18; r1.addTuple(myTuple);
  myTuple[0]=10; myTuple[1]=9; r1.addTuple(myTuple);

  myTuple[0]=10; myTuple[1]=11; r1.addTuple(myTuple);
  myTuple[0]=10; myTuple[1]=16; r1.addTuple(myTuple);
  myTuple[0]=11; myTuple[1]=9; r1.addTuple(myTuple);
  myTuple[0]=11; myTuple[1]=10; r1.addTuple(myTuple);
  myTuple[0]=11; myTuple[1]=14; r1.addTuple(myTuple);
  myTuple[0]=12; myTuple[1]=13; r1.addTuple(myTuple);
  myTuple[0]=12; myTuple[1]=14; r1.addTuple(myTuple);
  myTuple[0]=12; myTuple[1]=15; r1.addTuple(myTuple);
  myTuple[0]=13; myTuple[1]=12; r1.addTuple(myTuple);
  myTuple[0]=13; myTuple[1]=14; r1.addTuple(myTuple);

  myTuple[0]=14; myTuple[1]=11; r1.addTuple(myTuple);
  myTuple[0]=14; myTuple[1]=12; r1.addTuple(myTuple);
  myTuple[0]=14; myTuple[1]=13; r1.addTuple(myTuple);
  myTuple[0]=15; myTuple[1]=12; r1.addTuple(myTuple);
  myTuple[0]=15; myTuple[1]=16; r1.addTuple(myTuple);
  myTuple[0]=15; myTuple[1]=17; r1.addTuple(myTuple);
  myTuple[0]=16; myTuple[1]=10; r1.addTuple(myTuple);
  myTuple[0]=16; myTuple[1]=15; r1.addTuple(myTuple);
  myTuple[0]=16; myTuple[1]=17; r1.addTuple(myTuple);
  myTuple[0]=17; myTuple[1]=8; r1.addTuple(myTuple);

  myTuple[0]=17; myTuple[1]=15; r1.addTuple(myTuple);
  myTuple[0]=17; myTuple[1]=16; r1.addTuple(myTuple);
  myTuple[0]=18; myTuple[1]=9; r1.addTuple(myTuple);
  myTuple[0]=18; myTuple[1]=19; r1.addTuple(myTuple);
  myTuple[0]=18; myTuple[1]=20; r1.addTuple(myTuple);
  myTuple[0]=19; myTuple[1]=18; r1.addTuple(myTuple);
  myTuple[0]=19; myTuple[1]=20; r1.addTuple(myTuple);
  myTuple[0]=19; myTuple[1]=25; r1.addTuple(myTuple);
  myTuple[0]=20; myTuple[1]=18; r1.addTuple(myTuple);
  myTuple[0]=20; myTuple[1]=19; r1.addTuple(myTuple);

  myTuple[0]=20; myTuple[1]=23; r1.addTuple(myTuple);
  myTuple[0]=21; myTuple[1]=22; r1.addTuple(myTuple);
  myTuple[0]=21; myTuple[1]=23; r1.addTuple(myTuple);
  myTuple[0]=21; myTuple[1]=24; r1.addTuple(myTuple);
  myTuple[0]=22; myTuple[1]=4; r1.addTuple(myTuple);
  myTuple[0]=22; myTuple[1]=21; r1.addTuple(myTuple);
  myTuple[0]=22; myTuple[1]=23; r1.addTuple(myTuple);
  myTuple[0]=23; myTuple[1]=20; r1.addTuple(myTuple);
  myTuple[0]=23; myTuple[1]=21; r1.addTuple(myTuple);
  myTuple[0]=23; myTuple[1]=22; r1.addTuple(myTuple);

  myTuple[0]=24; myTuple[1]=21; r1.addTuple(myTuple);
  myTuple[0]=24; myTuple[1]=25; r1.addTuple(myTuple);
  myTuple[0]=24; myTuple[1]=26; r1.addTuple(myTuple);
  myTuple[0]=25; myTuple[1]=19; r1.addTuple(myTuple);
  myTuple[0]=25; myTuple[1]=24; r1.addTuple(myTuple);
  myTuple[0]=25; myTuple[1]=26; r1.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=24; r1.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=25; r1.addTuple(myTuple);

  Relation r2("R2",2);
  myTuple[0]=19; myTuple[1]=25; r2.addTuple(myTuple);
  myTuple[0]=21; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=24; myTuple[1]=25; r2.addTuple(myTuple);
  myTuple[0]=25; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=24; r2.addTuple(myTuple);
  myTuple[0]=26; myTuple[1]=25; r2.addTuple(myTuple);

  Variable** scp= new Variable*[2];
 scp[0]=&v0; scp[1]=&v1; Constraint c0("C0", 2, scp, r0);
 scp[0]=&v1; scp[1]=&v2; Constraint c1("C1", 2, scp, r1);
  scp[0]=&v2; scp[1]=&v3; Constraint c2("C2", 2, scp, r1);
  scp[0]=&v3; scp[1]=&v4; Constraint c3("C3", 2, scp, r1);
  scp[0]=&v4; scp[1]=&v5; Constraint c4("C4", 2, scp, r2);

  p.addConstraint(&c0);
  p.addConstraint(&c1);
  p.addConstraint(&c2);
  p.addConstraint(&c3);
  p.addConstraint(&c4);

#ifdef SHOWPROBLEM
  p.display();
#endif

  Solver s(p);
  s.doSearch();

  
  Problem p1;
  
  MyCallback cb(p1); // my interface between the parser and the solver

  if (argc!=2)
  {
    cout << "syntax: " << argv[0] << " CSPFile.xml\n"
	 << "  this program is a just a demonstration to illustrate how to use the CSP XML parser\n"
	 << endl;
    exit(1);
  }

  try
  {
    CSPXMLParser::XMLParser_libxml2<> parser(cb);

    parser.setPreferredExpressionRepresentation(INFIX_C);

    parser.parse(argv[1]); // parse the input file
    p1.display();

      Solver s1(p1);
      s1.doSearch();


  }
  catch (exception &e)
  {
    cout.flush();
    cerr << "\n\tUnexpected exception :\n";
    cerr << "\t" << e.what() << endl;
    exit(1);
  }


  return 0;
}
