//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Ellipse2DCutUserObject.h"

// MOOSE includes
#include "MooseError.h"

// XFEM includes
#include "XFEMFuncs.h"

template <>
InputParameters
validParams<Ellipse2DCutUserObject>()
{
  // Get input parameters from parent class
  InputParameters params = validParams<GeometricCut2DCurvesUserObject>();

  // Add required parameters
  params.addRequiredParam<std::vector<Real>>("cut_data",
                                             "Vector of Real values providing cut information");
  // Class description
  params.addClassDescription("Creates a UserObject for circular cuts on 2D meshes for XFEM");
  // Return the parameters
  return params;
}

Ellipse2DCutUserObject::Ellipse2DCutUserObject(const InputParameters & parameters)
  : GeometricCut2DCurvesUserObject(parameters), _cut_data(getParam<std::vector<Real>>("cut_data"))
{
  const int cut_data_len = 4;

  // Throw error if length of cut_data is incorrect
  if (_cut_data.size() != cut_data_len)
    mooseError("Length of Circle2DCutUserObject cut_data must be 3");

  // Assign cut_data to vars used to construct cuts
  _center = Point(_cut_data[0], _cut_data[1], 0.0);
  _major_axis = _cut_data[2];
  _minor_axis = _cut_data[3];
}

bool
Ellipse2DCutUserObject::intersectArcWithEdge(const Point & P1,
                                             const Point & P2,
                                             Real & segment_intersection_fraction) const
{
  bool has_intersection = false;
  //  if (isInsideArc(P1) == isInsideArc(P2))
  //  {
  //    // both nodes are either in or out, hence no intersection
  //    return has_intersection;
  //  }
  //  else
  //  {
  // https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm/
  Point seg_dir = P2 - P1;
  Point CtoP1 = P1 - _center;

  // we need to solve a quadratic equation for t.
  Real delta = -(CtoP1(0) * CtoP1(0) * seg_dir(1) * seg_dir(1)) +
               (2 * CtoP1(0) * CtoP1(1) * seg_dir(0) * seg_dir(1)) -
               (CtoP1(1) * CtoP1(1) * seg_dir(0) * seg_dir(0)) +
               (_major_axis * _major_axis * seg_dir(1) * seg_dir(1)) +
               (_minor_axis * _minor_axis * seg_dir(0) * seg_dir(0));
  if (delta > 0)
  {
    Real abDelta = _major_axis * _minor_axis * std::sqrt(delta);

    Real b = _minor_axis * _minor_axis * CtoP1(0) * seg_dir(0) +
             _major_axis * _major_axis * CtoP1(1) * seg_dir(1);
    Real denom = _major_axis * _major_axis * seg_dir(1) * seg_dir(1) +
                 _minor_axis * _minor_axis * seg_dir(0) * seg_dir(0);

    Real t1 = (-b + abDelta) / denom;
    Real t2 = (-b - abDelta) / denom;
    //
    if (t1 < 1.0 && t1 > 0.0)
    {
      segment_intersection_fraction = t1;
      has_intersection = true;
    }
    if (t2 < 1.0 && t2 > 0.0)
    {
      segment_intersection_fraction = t2;
      has_intersection = true;
    }
  }
  else
  {
    has_intersection = false;
    // std::cout << "no intersetction " << std::endl;
  }

  return has_intersection;
}

const std::vector<Point>
Ellipse2DCutUserObject::getCrackFrontPoints(unsigned int /*number_crack_front_points*/) const
{
  mooseError("getCrackFrontPoints() is not implemented for this object.");
}

bool
Ellipse2DCutUserObject::isInsideArc(const Point & p) const
{
  mooseError("isInsideArc() is not implemented for this object.");
  return false;
}
