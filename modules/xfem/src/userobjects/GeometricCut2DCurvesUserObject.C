/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "GeometricCut2DCurvesUserObject.h"

// MOOSE includes
#include "MooseError.h"

#include "libmesh/string_to_enum.h"

// XFEM includes
#include "XFEMFuncs.h"

template <>
InputParameters
validParams<GeometricCut2DCurvesUserObject>()
{
  // Get input parameters from parent class
  InputParameters params = validParams<GeometricCutUserObject>();

  // Class description
  params.addClassDescription("Base class for 2D XFEM Geometric Curves Cut UserObjects");
  // Return the parameters
  return params;
}

GeometricCut2DCurvesUserObject::GeometricCut2DCurvesUserObject(const InputParameters & parameters)
  : GeometricCutUserObject(parameters), _center()
{
  _cut_time_ranges.push_back(std::make_pair(0.0, 0.0));
}

bool GeometricCut2DCurvesUserObject::active(Real /*time*/) const
{
  // the current arc interfaces don't change with time
  return true;
}

bool
GeometricCut2DCurvesUserObject::cutElementByGeometry(const Elem * elem,
                                                     std::vector<CutEdge> & cut_edges,
                                                     std::vector<CutNode> & cut_nodes,
                                                     Real time) const
{
  bool cut_elem = false;

  // here goes algorithm
  for (unsigned int i = 0; i < elem->n_sides(); ++i)
  {
    // This returns the lowest-order type of side.
    std::unique_ptr<Elem> curr_side = elem->side(i);
    if (curr_side->type() != EDGE2)
      mooseError("In cutElementByGeometry dimension of side must be EDGE2, but it is ",
                 libMesh::Utility::enum_to_string(curr_side->type()),
                 " base element type is: ",
                 libMesh::Utility::enum_to_string(elem->type()));

    const Node * node1 = curr_side->get_node(0);
    const Node * node2 = curr_side->get_node(1);

    Real seg_int_frac = 0.0;

    // first check if the nodes are inside or outside
    if (intersectArcWithEdge(*node1, *node2, seg_int_frac))
    {
      if (seg_int_frac > Xfem::tol && seg_int_frac < 1.0 - Xfem::tol)
      {
        cut_elem = true;
        CutEdge mycut;
        mycut.id1 = node1->id();
        mycut.id2 = node2->id();
        mycut.distance = seg_int_frac;
        mycut.host_side_id = i;
        cut_edges.push_back(mycut);
      }
      else if (seg_int_frac < Xfem::tol)
      {
        cut_elem = true;
        CutNode mycut;
        mycut.id = node1->id();
        mycut.host_id = i;
        cut_nodes.push_back(mycut);
      }
    }
  }

  return cut_elem;
}

bool
GeometricCut2DCurvesUserObject::cutElementByGeometry(const Elem * /*elem*/,
                                                     std::vector<CutFace> & /*cut_faces*/,
                                                     Real /*time*/) const
{
  mooseError("Invalid method: must use vector of element edges for 2D mesh cutting");
  return false;
}

bool
GeometricCut2DCurvesUserObject::cutFragmentByGeometry(
    std::vector<std::vector<Point>> & /*frag_edges*/,
    std::vector<CutEdge> & /*cut_edges*/,
    Real /*time*/) const
{
  bool cut_elem = false;
  // here goes algorithm
  mooseError("GeometricCut2DCurvesUserObject::cutFragmentByGeometry Method not yet implemented");
  return cut_elem;
}

bool
GeometricCut2DCurvesUserObject::cutFragmentByGeometry(
    std::vector<std::vector<Point>> & /*frag_faces*/,
    std::vector<CutFace> & /*cut_faces*/,
    Real /*time*/) const
{
  mooseError("Invalid method: must use vector of element edges for 2D mesh cutting");
  return false;
}

bool
GeometricCut2DCurvesUserObject::intersectArcWithEdge(const Point & P1,
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
               (_radius * _radius * seg_dir(0) * seg_dir(0)) +
               (_radius * _radius * seg_dir(1) * seg_dir(1));
  if (delta > 0)
  {
    Real b = CtoP1(0) * seg_dir(0) + CtoP1(1) * seg_dir(1);
    Real denom = seg_dir(0) * seg_dir(0) + seg_dir(1) * seg_dir(1);

    Real t1 = (-b + std::sqrt(delta)) / denom;
    Real t2 = (-b - std::sqrt(delta)) / denom;
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

bool
GeometricCut2DCurvesUserObject::isInsideArc(const Point & p) const
{
  bool isInside = false;
  Real X_, Y_, R_;
  X_ = std::pow(p(0) - _center(0), 2);
  Y_ = std::pow(p(1) - _center(1), 2);
  R_ = std::pow(_radius, 2);

  if (X_ + Y_ - R_ < 0)
    isInside = true;

  return isInside;
}
