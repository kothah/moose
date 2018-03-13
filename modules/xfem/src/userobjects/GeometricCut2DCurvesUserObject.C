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

bool
GeometricCut2DCurvesUserObject::cutElementByGeometry(const Elem * elem,
                                                     std::vector<Xfem::CutEdge> & cut_edges,
                                                     std::vector<Xfem::CutNode> & cut_nodes,
                                                     Real /*time*/) const
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
        Xfem::CutEdge mycut;
        mycut._id1 = node1->id();
        mycut._id2 = node2->id();
        mycut._distance = seg_int_frac;
        mycut._host_side_id = i;
        cut_edges.push_back(mycut);
      }
      else if (seg_int_frac < Xfem::tol)
      {
        cut_elem = true;
        Xfem::CutNode mycut;
        mycut._id = node1->id();
        mycut._host_id = i;
        cut_nodes.push_back(mycut);
      }
    }
  }

  return cut_elem;
}

bool
GeometricCut2DCurvesUserObject::cutElementByGeometry(const Elem * /*elem*/,
                                                     std::vector<Xfem::CutFace> & /*cut_faces*/,
                                                     Real /*time*/) const
{
  mooseError("Invalid method: must use vector of element edges for 2D mesh cutting");
  return false;
}

bool
GeometricCut2DCurvesUserObject::cutFragmentByGeometry(
    std::vector<std::vector<Point>> & /*frag_edges*/,
    std::vector<Xfem::CutEdge> & /*cut_edges*/,
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
    std::vector<Xfem::CutFace> & /*cut_faces*/,
    Real /*time*/) const
{
  mooseError("Invalid method: must use vector of element edges for 2D mesh cutting");
  return false;
}
