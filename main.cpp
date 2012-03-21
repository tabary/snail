#include "Domain.h"
#include "Variable.h"

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

  // vector<int> const &tmp = d0.getInitialDomain();
  // for (int i=0; i< tmp.size(); i++)
  //   cout << tmp[i];
   
  // vector<int> const &tmp1 = d0.getCurrentDomain();
  // for (int i=0; i< tmp1.size(); i++)
  //   cout << tmp1[i]; 
  return 0;
}
