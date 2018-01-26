/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef GEOMETRICCUT2DCURVESUSEROBJECT_H
#define GEOMETRICCUT2DCURVESUSEROBJECT_H

#include "GeometricCutUserObject.h"

using namespace libMesh;

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
  double _radius;

  virtual bool
  intersectArcWithEdge(const Point & p1, const Point & p2, Real & cutting_line_fraction) const;

  virtual bool isInsideArc(const Point & p) const;

  Real crossProduct2D(const Point & point_a, const Point & point_b) const;
};

#endif // GEOMETRICCUT2DCURVESUSEROBJECT_H
