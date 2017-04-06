#ifndef HARDIKIC_H
#define HARDIKIC_H

// MOOSE Includes
#include "InitialCondition.h"

// Forward Declarations
class HardikIC;

template <>
InputParameters validParams<HardikIC>();

 // HardikIC just returns a constant value.

class HardikIC : public InitialCondition
{
public:

  // Constructor: Same as the rest of the MOOSE Objects
  HardikIC(const InputParameters & parameters);


  // The value of the variable at a point.
  // This must be overriden by derived classes.
  virtual Real value(const Point & p) override;

private:
  Real _coefficient;
};

#endif // HARDIKIC_H
