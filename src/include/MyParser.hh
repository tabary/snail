#include "XMLParser_libxml2.hh"
#include "global.hh"
#include "Problem.hh"
using namespace CSPXMLParser;

class MyCallback : public CSPParserCallback
{
private:
 // bool firstDomainValue;
 // bool firstTuple;
  string constraintReference;
  Problem &d_problem;
  Domain*tmpDomain;
  Domain** tmpDomains;
  size_t tmpDomainsSize;
  
  Relation*tmpRelation;
  Relation** tmpRelations;
  size_t tmpRelationsSize;
  
  
 // Domain** d_domainsCollection;
  //int d_nbDomains;
  //int d_currentDomain;
  
  //Relation **d_relationsCollection;
  //int d_nbRelations;
  //int d_currentRelation;
  
  
  
public:
    MyCallback(Problem &problem) : d_problem(problem)
    {  
    }
        
  virtual void beginInstance(const string & name)
  {
      d_problem.setName(name);
   }

  virtual void beginDomainsSection(int nbDomains) 
  {
    assert(nbDomains > 0);
    tmpDomains= new Domain*[nbDomains];
    tmpDomainsSize = nbDomains;
    for(auto i =0 ; i< nbDomains; ++i)
      tmpDomains[i] = NULL;
  }
  
  virtual void beginDomain(const string & name, int idDomain, int nbValue) 
  {
    assert(idDomain >= 0 && idDomain < (int) tmpDomainsSize && tmpDomain==NULL && tmpDomains[idDomain]==NULL);
    tmpDomains[idDomain] = new Domain(name, idDomain, nbValue);
    tmpDomain=tmpDomains[idDomain];
  }

  virtual void addDomainValue(int v) 
  {
    tmpDomain->addValue (v);
  }

  virtual void addDomainValue(int first,int last) 
  {
      tmpDomain->addIntervalValue(first,last);
  }

  virtual void endDomain() 
  {
      tmpDomain=NULL;
  }

  virtual void endDomainsSection() 
  { }

  virtual void beginVariablesSection(int nbVariables) 
  { 
    d_problem.initVariables(nbVariables);
  }
  
  virtual void addVariable(const string & name, int idVar,
			   const string & domain, int idDomain) 
  {
   Domain& d0 = *(tmpDomains[idDomain]);
   Variable* v = new Variable(name, *(new Domain(d0)),idVar);
   d_problem.addVariableAtIndex(v,idVar);
  }

  virtual void endVariablesSection() 
  {
      if (!d_problem.consolidateVariables())
        throw runtime_error("Variables not consolidated");
      for(size_t i=0; i < tmpDomainsSize; ++i)
        delete tmpDomains[i];        
      delete [] tmpDomains;
  }

  virtual void beginRelationsSection(int nbRelations) 
  {
    assert(nbRelations > 0);
    tmpRelations= new Relation*[nbRelations];
    tmpRelationsSize = nbRelations;
    for(auto i =0 ; i< nbRelations; ++i)
      tmpRelations[i] = NULL;
  }

    virtual void beginRelation(const string & name, int idRel,
			     int arity, int nbTuples, RelType relType) 
  {
      assert(idRel >= 0 && idRel < (int) tmpRelationsSize && arity > 0 && tmpRelation == NULL && tmpRelations[idRel] == NULL);        
      if (relType == REL_SOFT)        
        throw runtime_error("Not Supported");
          
    tmpRelation = new Relation(name, relType, arity, nbTuples);
    tmpRelations[idRel] = tmpRelation;
  }

  virtual void addRelationTuple(int arity, int tuple[]) 
  {      
    tmpRelation->addTuple (tuple);        
  }

  virtual void addRelationTuple(int arity, int tuple[], int cost) 
  {      
  throw runtime_error("Not Supported");
      // NOT IMPLEMENTED
  }

  virtual void endRelation() 
  {
    tmpRelation = NULL;
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
    d_problem.initConstraints (nbConstraints);
  }
  
  virtual void beginConstraint(const string & name, int idConstr,
			       int arity, 
			       const string & reference, 
			       CSPDefinitionType type, int id,
			       const ASTList &scope)
  {   
      Constraint* c = new Constraint(name, *(tmpRelations[id]),arity,idConstr);
      for(int i(0);i<scope.size();++i)       
          c->addVariableToScope(&(d_problem.getVariable(scope[i].getVarId())));
      d_problem.addConstraintAtIndex(c,idConstr);
      
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
  }

  virtual void endConstraintsSection() 
  {
    if (!d_problem.consolidateConstraints ())
      throw "Constraints not consolidated";
    delete [] tmpRelations;
  }

  virtual void endInstance() 
  { 
  }

};



