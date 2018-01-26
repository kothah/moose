/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef CIRCLE2DCUTUSEROBJECT_H
#define CIRCLE2DCUTUSEROBJECT_H

#include "GeometricCut2DCurvesUserObject.h"

// Forward declarations
class Circle2DCutUserObject;

template <>
InputParameters validParams<Circle2DCutUserObject>();

class Circle2DCutUserObject : public GeometricCut2DCurvesUserObject
{
public:
  Circle2DCutUserObject(const InputParameters & parameters);

  virtual void initialSetup() override{};
  virtual void initialize() override{};
  virtual void execute() override{};
  virtual void finalize() override{};
  virtual const std::vector<Point>
  getCrackFrontPoints(unsigned int num_crack_front_points) const override;

protected:
  std::vector<Real> _cut_data;

private:
  std::vector<Point> _vertices;
};

#endif // CIRCLE2DCUTUSEROBJECT_H
