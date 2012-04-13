/*=============================================================================
 * parser for CSP instances represented in XML format
 * 
 * Copyright (c) 2008 Olivier ROUSSEL (olivier.roussel <at> cril.univ-artois.fr)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *=============================================================================
 */

#include "include/XMLParser_libxml2.hh"

using namespace CSPXMLParser;

/*
 * A simple demo to illustrate how to use the XML CSP parser 
 */


/**
 * The methods of this class will be called by the XML parser to
 * report the elements of the definition of the CSP instance to your
 * own solver.
 *
 * This sample callback merely prints the data it receives. You must
 * modify it to transmit the informations to your solver.
 *
 * The description of each method can be found in
 * C++/include/CSPParserCallback.hh
 */
class MyCallback : public CSPParserCallback
{
private:
  bool firstDomainValue;
  bool firstTuple;
  string constraintReference;

public:
  virtual void beginInstance(const string & name)
  {
    cout << "<instance>" << endl;
    cout << "<presentation name='"
	 << name << "'/>" << endl;
  }

  virtual void beginDomainsSection(int nbDomains) 
  {  
    cout << "<domains nbDomains='" 
	 << nbDomains << "'>" <<endl;
  }
  
  virtual void beginDomain(const string & name, int idDomain, int nbValue) 
  {
    cout << " <domain name='" << name 
	 << "' nbValues='" << nbValue << "'>";
    firstDomainValue=true;
  }

  virtual void addDomainValue(int v) 
  {
    if (!firstDomainValue)
      cout << ' ';
    firstDomainValue=false;

    cout << v;
  }

  virtual void addDomainValue(int first,int last) 
  {
    if (!firstDomainValue)
      cout << ' ';
    firstDomainValue=false;

    cout << first << ".." << last;
  }

  virtual void endDomain() 
  {
    cout << "</domain>" <<endl;
  }

  /**
   * end the definition of all domains
   */
  virtual void endDomainsSection() 
  {
    cout << "</domains>" <<endl;
  }


  virtual void beginVariablesSection(int nbVariables) 
  {
    cout << "<variables nbVariables='"
	 << nbVariables << "'>" <<endl;
  }
  
  virtual void addVariable(const string & name, int idVar,
			   const string & domain, int idDomain) 
  {
    cout << "<variable name='" << name
	 << "' domain='" << domain 
	 << "'/>" <<endl;
  }

  virtual void endVariablesSection() 
  {
    cout << "</variables>" <<endl;
  }


  virtual void beginRelationsSection(int nbRelations) 
  {
    cout << "<relations nbRelations='" << nbRelations 
	 << "'>" <<endl;
  }

  
  virtual void beginRelation(const string & name, int idRel,
			     int arity, int nbTuples, RelType relType) 
  {
    cout << "<relation name='" << name 
	 << "' arity='" << arity << "' nbTuples='"
	 << nbTuples << "' semantics='";

    switch(relType)
    {
    case REL_SUPPORT:
      cout << "supports";
      break;
    case REL_CONFLICT:
      cout << "conflicts";
      break;
    case REL_SOFT:
      cout << "soft";
      break;
    default:
      throw runtime_error("unknown relation type");
    }

    cout << "'>";
    firstTuple=true;
  }

  virtual void addRelationTuple(int arity, int tuple[]) 
  {      
    if (!firstTuple)
      cout << '|';

    firstTuple=false;

    cout << tuple[0];
    for(int i=1;i<arity;++i)
      cout << ' ' << tuple[i];
  }

  virtual void addRelationTuple(int arity, int tuple[], int cost) 
  {      
    if (!firstTuple)
      cout << '|';

    firstTuple=false;

    cout << cost << ":" << tuple[0];
    for(int i=1;i<arity;++i)
      cout << ' ' << tuple[i];
  }

  virtual void endRelation() 
  {
    cout << "</relation>" <<endl;
  }

  virtual void endRelationsSection() 
  {
    cout << "</relations>" <<endl;
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
    cout << "<constraints nbConstraints='"
	 << nbConstraints << "'>" <<endl;
  }
  
  virtual void beginConstraint(const string & name, int idConstr,
			       int arity, 
			       const string & reference, 
			       CSPDefinitionType type, int id,
			       const ASTList &scope)
  {
    cout << "  <constraint name='" << name
	 << "' arity='" << arity 
	 << "' scope='";

    if (scope.size())
      cout << scope[0].getVarName();

    for(int i=1;i<scope.size();++i)
      cout << ' ' << scope[i].getVarName();

    cout << "' reference='" << reference 
	 << "'>" << endl;

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
      cout << "constraint parameters=";
      args.postfixExpression(cout);
      cout << endl;
    }
  } 


  virtual void endConstraint() 
  {
    cout << "  </constraint>" << endl;
  }

  /**
   * end the definition of all constraints
   */
  virtual void endConstraintsSection() 
  {
    cout << "</constraints>" <<endl;
  }

  /********************************************************************/


  /**
   * signal the end of parsing
   */
  virtual void endInstance() 
  {
    cout << "</instance>" <<endl;
  }

};



