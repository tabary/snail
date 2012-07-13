#include "include/XMLParser_libxml2.hh"
#include "../Problem.h"
using namespace CSPXMLParser;

class MyCallback : public CSPParserCallback
{
private:
  bool firstDomainValue;
  bool firstTuple;
  string constraintReference;
  Problem &d_problem;
  
  Domain** d_domainsCollection;
  int d_nbDomains;
  int d_currentDomain;
  
  Relation **d_relationsCollection;
  int d_nbRelations;
  int d_currentRelation;
  
  
  
public:
    MyCallback(Problem &problem) : d_problem(problem), d_nbDomains(0), d_currentDomain(-1),
                                                       d_nbRelations(0), d_currentRelation(0)
    {  
    }
        
  virtual void beginInstance(const string & name)
  {
      d_problem.setName(name);
   }

  virtual void beginDomainsSection(int nbDomains) 
  {  
      d_nbDomains = nbDomains;
  d_domainsCollection = new Domain*[nbDomains];  
  }
  
  virtual void beginDomain(const string & name, int idDomain, int nbValue) 
  {
    Domain * myDomain;
    myDomain = new Domain(name, nbValue);
    d_domainsCollection[idDomain] = myDomain;
    d_currentDomain = idDomain;
  }

  virtual void addDomainValue(int v) 
  {
      d_domainsCollection[d_currentDomain]->addValue(v);
  }

  virtual void addDomainValue(int first,int last) 
  {
      d_domainsCollection[d_currentDomain]->addIntervalValue(first,last);
  }

  virtual void endDomain() 
  {
      d_currentDomain = -1;
  }

  virtual void endDomainsSection() 
  { }

  virtual void beginVariablesSection(int nbVariables) 
  { }
  
  virtual void addVariable(const string & name, int idVar,
			   const string & domain, int idDomain) 
  {
   Domain  &d0 = *(d_domainsCollection[idDomain]);
   Variable* v;
   v = new Variable(name, *(new Domain(d0)));
   d_problem.addVariable(v);
   v->setId(d_problem.getVariablesCollection().size()-1);
  }

  virtual void endVariablesSection() 
  {
      for(int i=0; i < d_nbDomains; i++)
          delete d_domainsCollection[i];
  }

  virtual void beginRelationsSection(int nbRelations) 
  {
      d_nbRelations = nbRelations;
      d_relationsCollection = new Relation*[d_nbRelations];
      d_currentRelation = -1;
  }

    virtual void beginRelation(const string & name, int idRel,
			     int arity, int nbTuples, RelType relType) 
  {
       
        Relation * myRelation;
       //myRelation = new Relation(name, arity,relType);
            
    switch(relType)
    {
    case REL_SUPPORT:
        myRelation = new Relation(name, arity,0);
        break;
    case REL_CONFLICT:
        myRelation = new Relation(name, arity,1);
        break;
    case REL_SOFT:
           throw runtime_error("Not Supported");
      break;
    default:
      throw runtime_error("unknown relation type");
    }
    d_currentRelation = idRel;
    d_relationsCollection[idRel] = myRelation;
  }

  virtual void addRelationTuple(int arity, int tuple[]) 
  {      
            d_relationsCollection[d_currentRelation]->addTuple(tuple);
      
  }

  virtual void addRelationTuple(int arity, int tuple[], int cost) 
  {      
  throw runtime_error("Not Supported");
      // NOT IMPLEMENTED
  }

  virtual void endRelation() 
  {
  
  }

  virtual void endRelationsSection() 
  {
  }

  virtual void beginPredicatesSection(int nbPredicates) 
  {
    cout << "<predicates nbPredicates='" 
	 << nbPredicates << "'>" << endl;
  }
  
  virtual void beginPredicate(const string & name, int idPred) 
  {
    cout << "<predicate name='" << name 
	 << "'>" << endl;
  }

  virtual void addFormalParameter(int pos, const string & name, 
				  const string & type) 
  {
    cout << "   formal parameter " << pos << ": "
	 << type << " " << name << endl;
  }

  virtual void predicateExpression(AST *tree) 
  {
    cout << "   predicate definition (AST) = ";
    tree->prefixExpression(cout);
    cout << endl;
  }

  virtual void predicateExpression(const string &expr) 
  {
    cout << "   predicate definition=" << expr << endl;
  }

  virtual void endPredicate() 
  {
    cout << "</predicate>" << endl;
  }

  virtual void endPredicatesSection() 
  {
    cout << "</predicates>" << endl;
  }

  virtual void beginConstraintsSection(int nbConstraints) 
  {
 
  }
  
  
  Relation &getRelation(const string &reference)
  {
      for(int i=0; i< d_nbRelations; ++i)
      {
          if (d_relationsCollection[i]->getName() == reference)
              return *(d_relationsCollection[i]);
      }   
       throw runtime_error("Unreachable code");
  }
  
  
  
  
  virtual void beginConstraint(const string & name, int idConstr,
			       int arity, 
			       const string & reference, 
			       CSPDefinitionType type, int id,
			       const ASTList &scope)
  {   
      
      
      
      Constraint* c;
      c = new Constraint(name, arity, getRelation(reference));
      
      for(int i=0;i<scope.size();++i)
          c->addVariableToScope(&(d_problem.getVariable(scope[i].getVarId())));
      
      
      d_problem.addConstraint(c);
      
      vector<Variable *> &myScope = c->getScope();
      for(int i=0;i< (int) myScope.size();++i)
          myScope[i]->addConstraint(c);
       
      constraintReference=reference;
  }

  virtual void constraintParameters(const ASTList &args)
  {
    if (constraintReference=="global:cumulative")
    {
      const AST &tasks=args[0];
      const AST &limit=args[1];

      cout << "cumulative global constraint:\n  " 
	   << tasks.size() << " tasks are defined\n";

      for(int i=0;i<tasks.size();++i)
      {
	const AST &desc=tasks[i];
	cout << "    task " << i << "= ( ";
	if (desc.hasKey("origin"))
	{
	  cout << "origin=";
	  if (desc["origin"].isVar())
	    cout << desc["origin"].getVarName();
	  else
	    if (desc["origin"].isInteger())
	      cout << desc["origin"].getInteger();
	    else
	      cout << "?";

	  cout << ' ';
	}

	if (desc.hasKey("duration"))
	{
	  cout << "duration=";
	  if (desc["duration"].isVar())
	    cout << desc["duration"].getVarName();
	  else
	    if (desc["duration"].isInteger())
	      cout << desc["duration"].getInteger();
	    else
	      cout << "?";

	  cout << ' ';
	}

	if (desc.hasKey("end"))
	{
	  cout << "end=";
	  if (desc["end"].isVar())
	    cout << desc["end"].getVarName();
	  else
	    if (desc["end"].isInteger())
	      cout << desc["end"].getInteger();
	    else
	      cout << "?";

	  cout << ' ';
	}

	if (desc.hasKey("height"))
	{
	  cout << "height=";
	  if (desc["height"].isVar())
	    cout << desc["height"].getVarName();
	  else
	    if (desc["height"].isInteger())
	      cout << desc["height"].getInteger();
	    else
	      cout << "?";

	  cout << ' ';
	}

	cout << ")\n";
      }

      cout << "  limit=";
      if (limit.isVar())
	cout << limit.getVarName();
      else
	if (limit.isInteger())
	  cout << limit.getInteger();
	else
	  cout << "?";

      cout << endl;
    }
    else if (constraintReference=="global:element")
    {
      const AST &index=args[0];
      const AST &table=args[1];
      const AST &value=args[2];

      cout << "element global constraint:\n";

      cout << "  index=";
      if (index.isVar())
	cout << index.getVarName();
      else
	cout << index.getInteger();

      cout << "\n"
	   << "  table=[ ";

      for(int i=0;i<table.size();++i)
	if (table[i].isVar())
	  cout << table[i].getVarName() << ' ';
	else
	  cout << table[i].getInteger() << ' ';

      cout << "]\n"
	   << "  value=";

      if (value.isVar())
	cout << value.getVarName();
      else
	cout << value.getInteger();

      cout << endl;
	
    }
    else if (constraintReference=="global:weightedsum")
    {
      const AST &sum=args[0];
      const AST &op=args[1];
      const AST &rhs=args[2];

      cout << "weighted sum global constraint:\n";

      cout << sum[0]["coef"].getInteger() 
	   << "*" << sum[0]["var"].getVarName()
	   << showpos;

      for(int i=1;i<sum.size();++i)
	cout << sum[i]["coef"].getInteger() 
	     << "*" << sum[i]["var"].getVarName();

      cout << noshowpos;

      op.infixExpression(cout);

      if (rhs.isVar())
	cout << rhs.getVarName();
      else
	cout << rhs.getInteger();

      cout << endl;
    }
    else 
    {
      // default
      //cout << "constraint parameters=";
      //args.postfixExpression(cout);
      //cout << endl;
    }
  } 


  virtual void endConstraint() 
  {
  //  cout << "  </constraint>" << endl;
  }

  virtual void endConstraintsSection() 
  {
   // cout << "</constraints>" <<endl;
  }

  virtual void endInstance() 
  {
      delete d_domainsCollection;
      delete d_relationsCollection;  
  }

};



