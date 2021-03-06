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

#include "XFEMDispConstraint.h"

// MOOSE includes
#include "Assembly.h"
#include "ElementPairInfo.h"
#include "FEProblem.h"
#include "GeometricCutUserObject.h"
#include "XFEM.h"

#include "libmesh/quadrature.h"
#include "RankTwoTensor.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/quadrature.h"
#include "libmesh/utility.h"

#include "Material.h"
#include "SymmElasticityTensor.h"
#include "Kernel.h"

registerMooseObject("XFEMApp", XFEMDispConstraint);

template <>
InputParameters
validParams<XFEMDispConstraint>()
{
  InputParameters params = validParams<ElemElemConstraint>();
  params.addRequiredCoupledVar(
      "displacements",
      "The displacements appropriate for the simulation geometry and coordinate system");
  params.addParam<Real>("alpha", 100, "Stablization parameter in Nitsche's formulation.");
  params.addParam<UserObjectName>(
      "geometric_cut_userobject",
      "Name of GeometricCutUserObject associated with this constraint.");
  params.addRequiredParam<unsigned int>("component",
                                        "An integer corresponding to the direction "
                                        "the variable this kernel acts in. (0 for x, "
                                        "1 for y, 2 for z)");
  params.addParam<Real>("E", "Young's modulus of the material.");
  params.addParam<Real>("nu", "Poisson's ratio for the material.");

  params.addCoupledVar(
      "displacements",
      "The displacements appropriate for the simulation geometry and coordinate system");
  return params;
}

XFEMDispConstraint::XFEMDispConstraint(const InputParameters & parameters)
  : ElemElemConstraint(parameters),
    _component(getParam<unsigned int>("component")),
    _ndisp(coupledComponents("displacements")),
    _disp(3),
    _grad_disp(3),

    _disp_vars(3, nullptr),
    _disp_neighbor(3),
    _grad_disp_neighbor(3),

    _E(getParam<Real>("E")),
    _nu(getParam<Real>("nu")),
    _alpha(getParam<Real>("alpha"))
{
  _xfem = std::dynamic_pointer_cast<XFEM>(_fe_problem.getXFEM());
  if (_xfem == nullptr)
    mooseError("Problem casting to XFEM in XFEMDispConstraint");

  const UserObject * uo =
      &(_fe_problem.getUserObjectBase(getParam<UserObjectName>("geometric_cut_userobject")));

  if (dynamic_cast<const GeometricCutUserObject *>(uo) == nullptr)
    mooseError("UserObject casting to GeometricCutUserObject in XFEMDispConstraint");

  _interface_id = _xfem->getGeometricCutID(dynamic_cast<const GeometricCutUserObject *>(uo));

  //----------------------------------------------------------------------------------------------
  // displacements
  //
  if (_ndisp != _mesh.dimension())
    paramError(
        "displacements",
        "The number of variables supplied in 'displacements' must match the mesh dimension.");
  // fetch coupled variables and gradients (as stateful properties if necessary)
  for (unsigned int i = 0; i < _ndisp; ++i)
  {
    //_disp_var[i]= coupled("displacements", i);
    _disp[i] = &coupledValue("displacements", i);
    _grad_disp[i] = &coupledGradient("displacements", i);

    _disp_vars[i] = getVar("displacements", i);

    _disp_neighbor[i] = &_disp_vars[i]->slnNeighbor();
    _grad_disp_neighbor[i] = &_disp_vars[i]->gradSlnNeighbor();
  }

  // set unused dimensions to zero
  for (unsigned i = _ndisp; i < 3; ++i)
  {
    _disp[i] = &_zero;
    _grad_disp[i] = &_grad_zero;

    _disp_neighbor[i] = &_zero;
    _grad_disp_neighbor[i] = &_grad_zero;
  }

  // -- Elasticity tensor ---
  _Cijkl.fillSymmetricIsotropicEandNu(_E, _nu);
}

XFEMDispConstraint::~XFEMDispConstraint() {}

void
XFEMDispConstraint::reinitConstraintQuadrature(const ElementPairInfo & element_pair_info)
{
  _interface_normal = element_pair_info._elem1_normal;
  _interface_normal_neighbor = element_pair_info._elem2_normal;
  ElemElemConstraint::reinitConstraintQuadrature(element_pair_info);
}

Real
XFEMDispConstraint::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  Real norm_comp = _interface_normal(_component);

  // -----------------------------------------------------------------------------------------------
  // -- Compute contact pressure on the current element -------------------------------------------
  // -----------------------------------------------------------------------------------------------

  RankTwoTensor strain;
  RankTwoTensor stress;

  strain.zero();
  stress.zero();

  RankTwoTensor grad_tensor((*_grad_disp[0])[_qp], (*_grad_disp[1])[_qp], (*_grad_disp[2])[_qp]);
  strain = (grad_tensor + grad_tensor.transpose()) / 2.0;
  stress = _Cijkl * strain;

  // adding negative sign, as we know the contact stresses are negative already
  Real contact_pressure = -(stress * _interface_normal) * _interface_normal;

  // -- Compure contact pressure of the variation on the current element --------------------------

  RankTwoTensor test_strain;
  RankTwoTensor test_stress;

  test_strain.zero();
  test_stress.zero();

  RankTwoTensor grad_test_tensor(_grad_test[_i][_qp], _grad_test[_i][_qp], _grad_test[_i][_qp]);

  test_strain = (grad_test_tensor + grad_test_tensor.transpose()) / 2.0;
  test_stress = _Cijkl * test_strain;

  // adding negative sign, as we know the contact stresses are negative already
  Real test_contact_pressure = -(test_stress * _interface_normal) * _interface_normal;

  // -----------------------------------------------------------------------------------------------
  // -- Compute contact pressure on the Neighbor element -------------------------------------------
  // -----------------------------------------------------------------------------------------------

  RankTwoTensor strain_neighbor;
  RankTwoTensor stress_neighbor;

  strain_neighbor.zero();
  stress_neighbor.zero();

  RankTwoTensor grad_tensor_n((*_grad_disp_neighbor[0])[_qp],
                              (*_grad_disp_neighbor[1])[_qp],
                              (*_grad_disp_neighbor[2])[_qp]);
  strain_neighbor = (grad_tensor_n + grad_tensor_n.transpose()) / 2.0;
  stress_neighbor = _Cijkl * strain_neighbor;

  // adding negative sign, as we know the contact stresses are negative already
  Real contact_pressure_neighbor =
      -(stress_neighbor * _interface_normal_neighbor) * _interface_normal;

  // -- Compure contact pressure of the variation on the Neighbor element --------------------------

  RankTwoTensor test_strain_neighbor;
  RankTwoTensor test_stress_neighbor;

  test_strain_neighbor.zero();
  test_stress_neighbor.zero();

  RankTwoTensor grad_test_tensor_neighbor(
      _grad_test_neighbor[_i][_qp], _grad_test_neighbor[_i][_qp], _grad_test_neighbor[_i][_qp]);

  test_strain = (grad_test_tensor_neighbor + grad_test_tensor_neighbor.transpose()) / 2.0;
  test_stress = _Cijkl * test_strain_neighbor;

  // adding negative sign, as we know the contact stresses are negative already
  Real test_contact_pressure_neighbor =
      -(test_stress_neighbor * _interface_normal_neighbor) * _interface_normal;

  // -----------------------------------------------------------------------------------------------
  // -- kernel -------------------------------------------------------------------------------------
  // -----------------------------------------------------------------------------------------------

  switch (type)
  {
    case Moose::Element:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r -= (0.5 * (contact_pressure + contact_pressure_neighbor)) * (_test[_i][_qp] * norm_comp);
        r -= ((_u[_qp] - _u_neighbor[_qp]) * norm_comp) * (0.5 * test_contact_pressure);
        r += (_alpha / _current_elem->hmax()) * ((_u[_qp] - _u_neighbor[_qp]) * norm_comp) *
             (_test[_i][_qp] * norm_comp);
      }
      break;

    case Moose::Neighbor:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r += (0.5 * (contact_pressure + contact_pressure_neighbor)) *
             (_test_neighbor[_i][_qp] * norm_comp);
        r -= ((_u[_qp] - _u_neighbor[_qp]) * norm_comp) * (0.5 * test_contact_pressure_neighbor);
        r -= (_alpha / _neighbor_elem->hmax()) * ((_u[_qp] - _u_neighbor[_qp]) * norm_comp) *
             (_test_neighbor[_i][_qp] * norm_comp);
        break;
      }
  }

  return r;
}

Real
XFEMDispConstraint::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  Real norm_comp = _interface_normal(_component);

  // -----------------------------------------------------------------------------------------------
  // -- Compute contact pressure on the current element --------------------------------------------
  // -----------------------------------------------------------------------------------------------

  RankTwoTensor phi_strain;
  RankTwoTensor phi_stress;

  phi_strain.zero();
  phi_stress.zero();

  RankTwoTensor grad_phi_tensor(_grad_phi[_j][_qp], _grad_phi[_j][_qp], _grad_phi[_j][_qp]);
  phi_strain = (grad_phi_tensor + grad_phi_tensor.transpose()) / 2.0;
  phi_stress = _Cijkl * phi_strain;

  // adding negative sign, as we know the contact stresses are negative already
  Real phi_contact_pressure = -(phi_stress * _interface_normal) * _interface_normal;

  // -- Compure contact pressure of the variation on the current element --------------------------

  RankTwoTensor test_strain;
  RankTwoTensor test_stress;

  test_strain.zero();
  test_stress.zero();

  RankTwoTensor grad_test_tensor(_grad_test[_i][_qp], _grad_test[_i][_qp], _grad_test[_i][_qp]);

  test_strain = (grad_test_tensor + grad_test_tensor.transpose()) / 2.0;
  test_stress = _Cijkl * test_strain;

  // adding negative sign, as we know the contact stresses are negative already
  Real test_contact_pressure = -(test_stress * _interface_normal) * _interface_normal;

  // -----------------------------------------------------------------------------------------------
  // -- Compute contact pressure on the Neighbor element -------------------------------------------
  // -----------------------------------------------------------------------------------------------

  RankTwoTensor phi_strain_neighbor;
  RankTwoTensor phi_stress_neighbor;

  phi_strain_neighbor.zero();
  phi_stress_neighbor.zero();

  RankTwoTensor grad_phi_tensor_n(
      _grad_phi_neighbor[_j][_qp], _grad_phi_neighbor[_j][_qp], _grad_phi_neighbor[_j][_qp]);

  phi_strain_neighbor = (grad_phi_tensor_n + grad_phi_tensor_n.transpose()) / 2.0;
  phi_stress_neighbor = _Cijkl * phi_strain_neighbor;

  // adding negative sign, as we know the contact stresses are negative already
  Real phi_contact_pressure_neighbor =
      -(phi_stress_neighbor * _interface_normal_neighbor) * _interface_normal;

  // -- Compure contact pressure of the variation on the Neighbor element --------------------------

  RankTwoTensor test_strain_neighbor;
  RankTwoTensor test_stress_neighbor;

  test_strain_neighbor.zero();
  test_stress_neighbor.zero();

  RankTwoTensor grad_test_tensor_neighbor(
      _grad_test_neighbor[_i][_qp], _grad_test_neighbor[_i][_qp], _grad_test_neighbor[_i][_qp]);

  test_strain = (grad_test_tensor_neighbor + grad_test_tensor_neighbor.transpose()) / 2.0;
  test_stress = _Cijkl * test_strain_neighbor;

  // adding negative sign, as we know the contact stresses are negative already
  Real test_contact_pressure_neighbor =
      -(test_stress_neighbor * _interface_normal_neighbor) * _interface_normal;

  // -- kernel -------------------------------------------------------------------------------------

  switch (type)
  {
    case Moose::ElementElement:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r -= 0.5 * phi_contact_pressure * (_test[_i][_qp] * norm_comp);
        r -= (_phi[_j][_qp] * norm_comp) * (0.5 * test_contact_pressure);
        r += (_alpha / _current_elem->hmax()) * (_phi[_j][_qp] * norm_comp) *
             (_test[_i][_qp] * norm_comp);
      }
      break;

    case Moose::ElementNeighbor:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r -= 0.5 * phi_contact_pressure_neighbor * (_test[_i][_qp] * norm_comp);
        r += (_phi_neighbor[_j][_qp] * norm_comp) * (0.5 * test_contact_pressure);
        r -= (_alpha / _current_elem->hmax()) * (_phi_neighbor[_j][_qp] * norm_comp) *
             (_test[_i][_qp] * norm_comp);
      }
      break;

    case Moose::NeighborElement:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r += 0.5 * phi_contact_pressure * (_test_neighbor[_i][_qp] * norm_comp);
        r -= (_phi[_j][_qp] * norm_comp) * (0.5 * test_contact_pressure_neighbor);
        r -= (_alpha / _neighbor_elem->hmax()) * (_phi[_j][_qp] * norm_comp) *
             (_test_neighbor[_i][_qp] * norm_comp);
      }
      break;

    case Moose::NeighborNeighbor:
      if (((_u[_qp] - _u_neighbor[_qp]) * norm_comp) >= 0)
      {
        r += 0.5 * phi_contact_pressure_neighbor * (_test_neighbor[_i][_qp] * norm_comp);
        r += (_phi_neighbor[_j][_qp] * norm_comp) * (0.5 * test_contact_pressure_neighbor);
        r += (_alpha / _neighbor_elem->hmax()) * (_phi_neighbor[_j][_qp] * norm_comp) *
             (_test_neighbor[_i][_qp] * norm_comp);
      }
      break;
  }
  return r;
}
