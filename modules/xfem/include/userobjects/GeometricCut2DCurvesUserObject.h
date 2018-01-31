//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef GEOMETRICCUT2DCURVESUSEROBJECT_H
#define GEOMETRICCUT2DCURVESUSEROBJECT_H

#include "GeometricCutUserObject.h"
using namespace libMesh;
// Forward declarations
class GeometricCut2DCurvesUserObject;

template <>
InputParameters validParams<GeometricCut2DCurvesUserObject>();

class GeometricCut2DCurvesUserObject : public GeometricCutUserObject
{
public:
  GeometricCut2DCurvesUserObject(const InputParameters & parameters);

  virtual bool active(Real time) const override;

  virtual bool cutElementByGeometry(const Elem * elem,
                                    std::vector<CutEdge> & cut_edges,
                                    std::vector<CutNode> & cut_nodes,
                                    Real time) const override;
  virtual bool cutElementByGeometry(const Elem * elem,
                                    std::vector<CutFace> & cut_faces,
                                    Real time) const override;

  virtual bool cutFragmentByGeometry(std::vector<std::vector<Point>> & frag_edges,
                                     std::vector<CutEdge> & cut_edges,
                                     Real time) const override;
  virtual bool cutFragmentByGeometry(std::vector<std::vector<Point>> & frag_faces,
                                     std::vector<CutFace> & cut_faces,
                                     Real time) const override;

protected:
  Point _center;

  virtual bool intersectArcWithEdge(const Point & p1,
                                    const Point & p2,
                                    Real & segment_intersection_fraction) const = 0;

  virtual bool isInsideArc(const Point & p) const = 0;
};

#endif // GEOMETRICCUT2DCURVESUSEROBJECT_H
