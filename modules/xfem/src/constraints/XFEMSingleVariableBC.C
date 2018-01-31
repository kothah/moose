/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "XFEMSingleVariableBC.h"

// MOOSE includes
#include "Assembly.h"
#include "ElementPairInfo.h"
#include "FEProblem.h"

#include "libmesh/quadrature.h"

template <>
InputParameters
validParams<XFEMSingleVariableBC>()
{
  InputParameters params = validParams<ElemElemConstraint>();
  params.addParam<Real>("alpha", 10, "Stablization parameter in Nitsche's formulation.");
  params.addParam<Real>("gamma", 10E-8, "Stablization parameter in Fictitious formulation.");
  params.addParam<Real>("dirichlet", 0, "Jump at the interface.");
  return params;
}

XFEMSingleVariableBC::XFEMSingleVariableBC(const InputParameters & parameters)
  : ElemElemConstraint(parameters),
    _alpha(getParam<Real>("alpha")),
    _gamma(getParam<Real>("gamma")),
    _dirichlet(getParam<Real>("dirichlet"))
{
}

XFEMSingleVariableBC::~XFEMSingleVariableBC() {}

void
XFEMSingleVariableBC::reinitConstraintQuadrature(const ElementPairInfo & element_pair_info)
{
  _interface_normal = element_pair_info._elem1_normal;
  _elem1_vol_frac = element_pair_info._elem1_physical_volfrac;
  _elem2_vol_frac = element_pair_info._elem2_physical_volfrac;

  ElemElemConstraint::reinitConstraintQuadrature(element_pair_info);
}

Real
XFEMSingleVariableBC::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  switch (type)
  {
    case Moose::Element:
      r -= _grad_u[_qp] * _interface_normal * _test[_i][_qp];
      r -= (_u[_qp] - _dirichlet) * _grad_test[_i][_qp] * _interface_normal;
      r += (_alpha / _current_elem->hmax()) * (_u[_qp] - _dirichlet) * _test[_i][_qp];
      r += (_gamma * _current_elem->hmax()) *
           (_grad_u[_qp] * _interface_normal - _grad_u_neighbor[_qp] * _interface_normal) *
           _grad_test[_i][_qp] * _interface_normal;
      break;

    case Moose::Neighbor:
      r += _grad_u_neighbor[_qp] * _interface_normal * _test_neighbor[_i][_qp];
      r += (_u_neighbor[_qp] - _dirichlet) * _grad_test_neighbor[_i][_qp] * _interface_normal;
      r += (_alpha / _neighbor_elem->hmax()) * (_u_neighbor[_qp] - _dirichlet) *
           _test_neighbor[_i][_qp];
      r -= (_gamma * _neighbor_elem->hmax()) *
           (_grad_u[_qp] * _interface_normal - _grad_u_neighbor[_qp] * _interface_normal) *
           _grad_test_neighbor[_i][_qp] * _interface_normal;
      break;
  }
  return r;
}

Real
XFEMSingleVariableBC::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  switch (type)
  {
    case Moose::ElementElement:
      r -= _grad_phi[_j][_qp] * _interface_normal * _test[_i][_qp];
      r -= _phi[_j][_qp] * _grad_test[_i][_qp] * _interface_normal;
      r += (_alpha / _current_elem->hmax()) * _phi[_j][_qp] * _test[_i][_qp];
      r += (_gamma * _current_elem->hmax()) * (_grad_phi[_j][_qp] * _interface_normal) *
           _grad_test[_i][_qp] * _interface_normal;

      break;

    case Moose::ElementNeighbor:
      r -= (_gamma * _current_elem->hmax()) * (_grad_phi_neighbor[_j][_qp] * _interface_normal) *
           _grad_test[_i][_qp] * _interface_normal;
      break;

    case Moose::NeighborElement:
      r -= (_gamma * _neighbor_elem->hmax()) * (_grad_phi[_j][_qp] * _interface_normal) *
           _grad_test_neighbor[_i][_qp] * _interface_normal;
      break;

    case Moose::NeighborNeighbor:
      r += _grad_phi_neighbor[_j][_qp] * _interface_normal * _test_neighbor[_i][_qp];
      r += _phi_neighbor[_j][_qp] * _grad_test_neighbor[_i][_qp] * _interface_normal;
      r += (_alpha / _neighbor_elem->hmax()) * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      r += (_gamma * _neighbor_elem->hmax()) * (_grad_phi_neighbor[_j][_qp] * _interface_normal) *
           _grad_test_neighbor[_i][_qp] * _interface_normal;
      break;
  }

  return r;
}
