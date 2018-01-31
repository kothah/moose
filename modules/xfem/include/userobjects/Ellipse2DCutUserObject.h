//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ELLIPSE2DCUTUSEROBJECT_H
#define ELLIPSE2DCUTUSEROBJECT_H

#include "GeometricCut2DCurvesUserObject.h"

// Forward declarations
class Ellipse2DCutUserObject;

template <>
InputParameters validParams<Ellipse2DCutUserObject>();

class Ellipse2DCutUserObject : public GeometricCut2DCurvesUserObject
{
public:
  Ellipse2DCutUserObject(const InputParameters & parameters);

  virtual void initialSetup() override{};
  virtual void initialize() override{};
  virtual void execute() override{};
  virtual void finalize() override{};
  virtual const std::vector<Point>
  getCrackFrontPoints(unsigned int num_crack_front_points) const override;

protected:
  std::vector<Real> _cut_data;

  bool intersectArcWithEdge(const Point & p1,
                            const Point & p2,
                            Real & segment_intersection_fraction) const override;
  virtual bool isInsideArc(const Point & p) const override;

private:
  Real _major_axis;
  Real _minor_axis;
};

#endif // ELLIPSE2DCUTUSEROBJECT_H
