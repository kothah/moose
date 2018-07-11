//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/*       XFEM - ICS XFEM simulation framework                   */
/*                Prepared by Hardik Kothari,                   */
/*                  ICS, USI, 6900 Lugano                       */
/*                                                              */
/* Construction of XFEM kernels for conatct and other interface */
/* problems                                                     */
/****************************************************************/

#include "XFEMSingleVariableInEqConstraint.h"

// MOOSE includes
#include "Assembly.h"
#include "ElementPairInfo.h"
#include "FEProblem.h"
#include "GeometricCutUserObject.h"
#include "XFEM.h"

#include "libmesh/quadrature.h"

registerMooseObject("XFEMApp", XFEMSingleVariableInEqConstraint);

template <>
InputParameters
validParams<XFEMSingleVariableInEqConstraint>()
{
  InputParameters params = validParams<ElemElemConstraint>();
  params.addParam<Real>("alpha", 100, "Stablization parameter in Nitsche's formulation.");
  params.addParam<Real>("time_from", 0, "time when the constraint is activated.");
  params.addParam<Real>("time_to", 0, "time when the constraint is deactivated.");
  params.addParam<UserObjectName>(
      "geometric_cut_userobject",
      "Name of GeometricCutUserObject associated with this constraint.");
  params.addParam<bool>(
      "use_penalty",
      false,
      "Use the Penalty instead of Nitsche (Nitsche only works for simple diffusion problem).");
  return params;
}

XFEMSingleVariableInEqConstraint::XFEMSingleVariableInEqConstraint(
    const InputParameters & parameters)
  : ElemElemConstraint(parameters),
    _alpha(getParam<Real>("alpha")),
    _time_from(getParam<Real>("time_from")),
    _time_to(getParam<Real>("time_to")),
    _use_penalty(getParam<bool>("use_penalty"))
{
  _xfem = std::dynamic_pointer_cast<XFEM>(_fe_problem.getXFEM());
  if (_xfem == nullptr)
    mooseError("Problem casting to XFEM in XFEMSingleVariableInEqConstraint");

  const UserObject * uo =
      &(_fe_problem.getUserObjectBase(getParam<UserObjectName>("geometric_cut_userobject")));

  if (dynamic_cast<const GeometricCutUserObject *>(uo) == nullptr)
    mooseError("UserObject casting to GeometricCutUserObject in XFEMSingleVariableInEqConstraint");

  _interface_id = _xfem->getGeometricCutID(dynamic_cast<const GeometricCutUserObject *>(uo));
  std::cout << "interface id: " << _interface_id << std::endl;
}

XFEMSingleVariableInEqConstraint::~XFEMSingleVariableInEqConstraint() {}

void
XFEMSingleVariableInEqConstraint::reinitConstraintQuadrature(
    const ElementPairInfo & element_pair_info)
{
  _interface_normal = element_pair_info._elem1_normal;
  ElemElemConstraint::reinitConstraintQuadrature(element_pair_info);
}

Real
XFEMSingleVariableInEqConstraint ::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;
  if ((_fe_problem.time() >= _time_from) && (_fe_problem.time() <= _time_to))
  {
    switch (type)
    {
      case Moose::Element:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {
          if (!_use_penalty)
          {
            r -= (0.5 * _grad_u[_qp] * _interface_normal +
                  0.5 * _grad_u_neighbor[_qp] * _interface_normal) *
                 _test[_i][_qp];
            r -= (_u[_qp] - _u_neighbor[_qp]) * 0.5 * _grad_test[_i][_qp] * _interface_normal;
          }
          r += (_alpha / _current_elem->hmax()) * (_u[_qp] - _u_neighbor[_qp]) * _test[_i][_qp];
        }
        break;

      case Moose::Neighbor:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {
          if (!_use_penalty)
          {
            r += (0.5 * _grad_u[_qp] * _interface_normal +
                  0.5 * _grad_u_neighbor[_qp] * _interface_normal) *
                 _test_neighbor[_i][_qp];
            r -= (_u[_qp] - _u_neighbor[_qp]) * 0.5 * _grad_test_neighbor[_i][_qp] *
                 _interface_normal;
          }
          r -= (_alpha / _neighbor_elem->hmax()) * (_u[_qp] - _u_neighbor[_qp]) *
               _test_neighbor[_i][_qp];
          break;
        }
    }
  }
  return r;
}

Real
XFEMSingleVariableInEqConstraint ::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;
  if ((_fe_problem.time() >= _time_from) && (_fe_problem.time() <= _time_to))
  {
    switch (type)
    {
      case Moose::ElementElement:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {

          if (!_use_penalty)
            r += -0.5 * _grad_phi[_j][_qp] * _interface_normal * _test[_i][_qp] -
                 _phi[_j][_qp] * 0.5 * _grad_test[_i][_qp] * _interface_normal;
          r += (_alpha / _current_elem->hmax()) * _phi[_j][_qp] * _test[_i][_qp];
        }
        break;

      case Moose::ElementNeighbor:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {
          if (!_use_penalty)
            r += -0.5 * _grad_phi_neighbor[_j][_qp] * _interface_normal * _test[_i][_qp] +
                 _phi_neighbor[_j][_qp] * 0.5 * _grad_test[_i][_qp] * _interface_normal;
          r -= (_alpha / _current_elem->hmax()) * _phi_neighbor[_j][_qp] * _test[_i][_qp];
        }
        break;

      case Moose::NeighborElement:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {
          if (!_use_penalty)
            r += 0.5 * _grad_phi[_j][_qp] * _interface_normal * _test_neighbor[_i][_qp] -
                 _phi[_j][_qp] * 0.5 * _grad_test_neighbor[_i][_qp] * _interface_normal;
          r -= (_alpha / _neighbor_elem->hmax()) * _phi[_j][_qp] * _test_neighbor[_i][_qp];
        }
        break;

      case Moose::NeighborNeighbor:
        if ((_u[_qp] - _u_neighbor[_qp]) >= 0)
        {
          if (!_use_penalty)
            r += 0.5 * _grad_phi_neighbor[_j][_qp] * _interface_normal * _test_neighbor[_i][_qp] +
                 _phi_neighbor[_j][_qp] * 0.5 * _grad_test_neighbor[_i][_qp] * _interface_normal;
          r += (_alpha / _neighbor_elem->hmax()) * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
        }
        break;
    }
  }
  return r;
}
