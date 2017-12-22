/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef CIRCULARSEGMENTCUTUSEROBJECT_H
#define CIRCULARSEGMENTCUTUSEROBJECT_H

#include "GeometricCut2DUserObject.h"

// Forward declarations
class CircularSegmentCutUserObject;
template <>
InputParameters validParams<CircularSegmentCutUserObject>();

class CircularSegmentCutUserObject : public GeometricCut2DUserObject
{
public:
  CircularSegmentCutUserObject(const InputParameters & parameters);

  virtual void initialize() override{};
  virtual void execute() override{};
  virtual void finalize() override{};
  virtual const std::vector<Point>
  getCrackFrontPoints(unsigned int num_crack_front_points) const override;

protected:
  std::vector<Real> _cut_data;
  std::vector<Real> _center;
  std::vector<Real> _radius;
};

#endif // CIRCULARTSEGMENTCUTUSEROBJECT_H
