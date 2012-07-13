#include "Solver.h"
#include "parser/MyParser.h"
#include <time.h>

using namespace std;

int main(int argc, char **argv) {

    clock_t initialTime = clock();
        
    cout << "Hello from SnaiL \n";
    Problem p;
    MyCallback cb(p); // my interface between the parser and the solver

    if (argc != 2) {
        cout << "syntax: " << argv[0] << " CSPFile.xml\n" << endl;
        exit(1);
    }

    try {
        CSPXMLParser::XMLParser_libxml2<> parser(cb);
        parser.setPreferredExpressionRepresentation(INFIX_C);
        parser.parse(argv[1]); // parse the input file

#ifdef SHOWPROBLEM
        p.display();
#endif   
       
        Solver s(p);
        s.doSearch(); 
       
        cout << "Total time : " << ((double) (clock()- initialTime))/ CLOCKS_PER_SEC  << endl;
    
    } catch (exception &e) {
        cout.flush();
        cerr << "\n\tUnexpected exception :\n";
        cerr << "\t" << e.what() << endl;
        exit(1);
    }

    return 0;
}
