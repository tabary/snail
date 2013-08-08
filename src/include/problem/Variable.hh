#ifndef DEF_VARIABLE
#define DEF_VARIABLE

#include "Domain.hh"
#include "Constraint.hh"

#include <cassert>

class Constraint;

class Variable
{
private:
  static unsigned int nbAssigned;

  std::string _name;
  
  Domain &_domain;
  unsigned int _id;

  bool _assigned;
  
  std::vector <Constraint *> _involvedConstraints;

  
public:
  Variable (const std::string &name, Domain &domain, int variableId); // The associated domain must be previously created

  static unsigned int getNbAssigned ();
  static void setNbAssigned (unsigned int nb);

  void addConstraint (Constraint *constraint);

  Domain &getDomain () const;
  std::string const &getName () const;
  std::vector <Constraint *> const &getInvolvedConstraints () const;

  unsigned int getIndex () const;

  unsigned int getDegree () const;
  unsigned int getDDegree () const;

  bool isAssigned () const;
  void setAssigned (bool a);

  bool hasEmptyDomain () const;

  friend std::ostream& operator<< (std::ostream &flux, const Variable &variable);
};

#endif
