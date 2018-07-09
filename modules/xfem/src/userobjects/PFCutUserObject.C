/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

/* Author: Hardik Kothari
 * Based on LevelSetCutUserObject
 * */

#include "PFCutUserObject.h"
#include "SubProblem.h"
#include "MooseVariable.h"
#include "libmesh/string_to_enum.h"

template <>
InputParameters
validParams<PFCutUserObject>()
{
  InputParameters params = validParams<GeometricCutUserObject>();
  params.addRequiredParam<VariableName>(
      "pf_var", "The name of phasefiled variable used to represent the interface");
  params.addClassDescription("XFEM mesh cut by phase field function");
  return params;
}

PFCutUserObject::PFCutUserObject(const InputParameters & parameters)
  : GeometricCutUserObject(parameters),
    _pf_var_number(_subproblem
                       .getVariable(_tid,
                                    parameters.get<VariableName>("pf_var"),
                                    Moose::VarKindType::VAR_ANY,
                                    Moose::VarFieldType::VAR_FIELD_STANDARD)
                       .number()),
    _system(_subproblem.getSystem(getParam<VariableName>("pf_var"))),
    _solution(_system.current_local_solution.get())
{
}

bool
PFCutUserObject::cutElementByGeometry(const Elem * elem,
                                      std::vector<Xfem::CutEdge> & cut_edges,
                                      std::vector<Xfem::CutNode> & /*cut_nodes*/,
                                      Real /*time*/) const
{
  bool cut_elem = false;
  bool isCandidate[4] = {false};
  unsigned int num_neighbors = 0;

  // adaptation for phase field
  if (elem->type() != QUAD4)
  {
    mooseError("In PFCutUserObject element side must be QUAD4, but type is: ",
               libMesh::Utility::enum_to_string(elem->type()),
               " base element type is: ",
               libMesh::Utility::enum_to_string(elem->type()));
  }
  else
  {
    const Node * node1 = elem->node_ptr(0);
    const Node * node2 = elem->node_ptr(1);
    const Node * node3 = elem->node_ptr(2);
    const Node * node4 = elem->node_ptr(3);

    std::array<const Node *, 8> Neighbor_edges;

    dof_id_type ls_dof_id_1 = node1->dof_number(_system.number(), _pf_var_number, 0);
    dof_id_type ls_dof_id_2 = node2->dof_number(_system.number(), _pf_var_number, 0);
    dof_id_type ls_dof_id_3 = node3->dof_number(_system.number(), _pf_var_number, 0);
    dof_id_type ls_dof_id_4 = node4->dof_number(_system.number(), _pf_var_number, 0);

    Number ls_node_1 = (*_solution)(ls_dof_id_1);
    Number ls_node_2 = (*_solution)(ls_dof_id_2);
    Number ls_node_3 = (*_solution)(ls_dof_id_3);
    Number ls_node_4 = (*_solution)(ls_dof_id_4);

    if (ls_node_1 > 0.95 && ls_node_2 > 0.95 && ls_node_3 > 0.95 && ls_node_4 > 0.95)
    {
      UniquePtr<Elem> curr_side0 = elem->side(0);
      UniquePtr<Elem> curr_side1 = elem->side(1);
      UniquePtr<Elem> curr_side2 = elem->side(2);
      UniquePtr<Elem> curr_side3 = elem->side(3);

      const Elem * n_elem0 = elem->neighbor_ptr(0);
      const Elem * n_elem1 = elem->neighbor_ptr(1);
      const Elem * n_elem2 = elem->neighbor_ptr(2);
      const Elem * n_elem3 = elem->neighbor_ptr(3);

      if (n_elem0 != nullptr)
      {
        num_neighbors += 1;

        UniquePtr<Elem> curr_side0 = n_elem0->side(0);
        const Node * nnode0_1 = curr_side0->node_ptr(0);
        const Node * nnode0_2 = curr_side0->node_ptr(1);
        Neighbor_edges[0] = nnode0_1;
        Neighbor_edges[1] = nnode0_2;
      }
      else
      {
        Neighbor_edges[0] = nullptr;
        Neighbor_edges[1] = nullptr;
      }

      if (n_elem1 != nullptr)
      {
        num_neighbors += 1;

        UniquePtr<Elem> curr_side1 = n_elem1->side(1);
        const Node * nnode1_1 = curr_side1->node_ptr(0);
        const Node * nnode1_2 = curr_side1->node_ptr(1);
        Neighbor_edges[2] = nnode1_1;
        Neighbor_edges[3] = nnode1_2;
      }
      else
      {
        Neighbor_edges[2] = nullptr;
        Neighbor_edges[3] = nullptr;
      }

      if (n_elem2 != nullptr)
      {
        num_neighbors += 1;

        UniquePtr<Elem> curr_side2 = n_elem2->side(2);
        const Node * nnode2_1 = curr_side2->node_ptr(0);
        const Node * nnode2_2 = curr_side2->node_ptr(1);
        Neighbor_edges[4] = nnode2_1;
        Neighbor_edges[5] = nnode2_2;
      }
      else
      {
        Neighbor_edges[4] = nullptr;
        Neighbor_edges[5] = nullptr;
      }
      if (n_elem3 != nullptr)
      {
        num_neighbors += 1;

        UniquePtr<Elem> curr_side3 = n_elem3->side(3);
        const Node * nnode3_1 = curr_side3->node_ptr(0);
        const Node * nnode3_2 = curr_side3->node_ptr(1);
        Neighbor_edges[6] = nnode3_1;
        Neighbor_edges[7] = nnode3_2;
      }
      else
      {
        Neighbor_edges[6] = nullptr;
        Neighbor_edges[7] = nullptr;
      }

      // get the nodal values
      for (unsigned int in = 0; in < 8; in += 2)
      {
        if (Neighbor_edges[in] != nullptr)
        {
          dof_id_type ls_dof_id_1 =
              Neighbor_edges[in]->dof_number(_system.number(), _pf_var_number, 0);
          dof_id_type ls_dof_id_2 =
              Neighbor_edges[in + 1]->dof_number(_system.number(), _pf_var_number, 0);

          Number ls_node_1 = (*_solution)(ls_dof_id_1);
          Number ls_node_2 = (*_solution)(ls_dof_id_2);
          if (ls_node_1 > 0.95 && ls_node_2 > 0.95)
            isCandidate[in / 2] = true;
        }
      }
    }
    // use the information form the above section here to cut the current element

    for (unsigned int i = 0; i < elem->n_sides(); ++i)
    {
      std::unique_ptr<Elem> curr_side = elem->side(i);
      if (curr_side->type() != EDGE2)
        mooseError("In PFCutUserObject element side must be EDGE2, but type is: ",
                   libMesh::Utility::enum_to_string(curr_side->type()),
                   " base element type is: ",
                   libMesh::Utility::enum_to_string(elem->type()));
      const Node * node1 = curr_side->get_node(0);
      const Node * node2 = curr_side->get_node(1);

      if (isCandidate[i] == 1 && num_neighbors == 4)
      {
        cut_elem = true;
        Xfem::CutEdge mycut;
        mycut._id1 = node1->id();
        mycut._id2 = node2->id();

        Real seg_int_frac = 0.5;
        mycut._distance = seg_int_frac;
        mycut._host_side_id = i;
        cut_edges.push_back(mycut);
      }
      else if (num_neighbors == 3)
      {
        if (isCandidate[i] == 1 || isCandidate[i % 2] == 1)
        {
          cut_elem = true;
          Xfem::CutEdge mycut;
          mycut._id1 = node1->id();
          mycut._id2 = node2->id();

          Real seg_int_frac = 0.5;
          mycut._distance = seg_int_frac;
          mycut._host_side_id = i;
          cut_edges.push_back(mycut);
        }
      }
    }
  }
  return cut_elem;
}

bool
PFCutUserObject::cutElementByGeometry(const Elem * elem,
                                      std::vector<Xfem::CutFace> & cut_faces,
                                      Real /*time*/) const
{
  bool cut_elem = false;

  for (unsigned int i = 0; i < elem->n_sides(); ++i)
  {
    std::unique_ptr<Elem> curr_side = elem->side(i);
    if (curr_side->dim() != 2)
      mooseError("In LevelSetCutUserObject dimension of side must be 2, but it is ",
                 curr_side->dim());
    unsigned int n_edges = curr_side->n_sides();

    std::vector<unsigned int> cut_edges;
    std::vector<Real> cut_pos;

    for (unsigned int j = 0; j < n_edges; j++)
    {
      // This returns the lowest-order type of side.
      std::unique_ptr<Elem> curr_edge = curr_side->side(j);
      if (curr_edge->type() != EDGE2)
        mooseError("In LevelSetCutUserObject face edge must be EDGE2, but type is: ",
                   libMesh::Utility::enum_to_string(curr_edge->type()),
                   " base element type is: ",
                   libMesh::Utility::enum_to_string(elem->type()));

      const Node * node1 = curr_edge->get_node(0);
      const Node * node2 = curr_edge->get_node(1);

      dof_id_type ls_dof_id_1 = node1->dof_number(_system.number(), _pf_var_number, 0);
      dof_id_type ls_dof_id_2 = node2->dof_number(_system.number(), _pf_var_number, 0);

      Number ls_node_1 = (*_solution)(ls_dof_id_1);
      Number ls_node_2 = (*_solution)(ls_dof_id_2);

      if (ls_node_1 * ls_node_2 < 0)
      {
        Real seg_int_frac = std::abs(ls_node_1) / std::abs(ls_node_1 - ls_node_2);
        cut_edges.push_back(j);
        cut_pos.push_back(seg_int_frac);
      }
    }

    if (cut_edges.size() == 2)
    {
      cut_elem = true;
      Xfem::CutFace mycut;
      mycut._face_id = i;
      mycut._face_edge.push_back(cut_edges[0]);
      mycut._face_edge.push_back(cut_edges[1]);
      mycut._position.push_back(cut_pos[0]);
      mycut._position.push_back(cut_pos[1]);
      cut_faces.push_back(mycut);
    }
  }
  return cut_elem;
}

bool
PFCutUserObject::cutFragmentByGeometry(std::vector<std::vector<Point>> & /*frag_edges*/,
                                       std::vector<Xfem::CutEdge> & /*cut_edges*/,
                                       Real /*time*/) const
{
  return false;
}

bool
PFCutUserObject::cutFragmentByGeometry(std::vector<std::vector<Point>> & /*frag_faces*/,
                                       std::vector<Xfem::CutFace> & /*cut_faces*/,
                                       Real /*time*/) const
{
  mooseError("cutFragmentByGeometry not yet implemented for 3d level set cutting");
  return false;
}

const std::vector<Point>
PFCutUserObject::getCrackFrontPoints(unsigned int /*num_crack_front_points*/) const
{
  mooseError("getCrackFrontPoints() is not implemented for this object.");
}
