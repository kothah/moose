//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

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
};

#endif // CIRCLE2DCUTUSEROBJECT_H
