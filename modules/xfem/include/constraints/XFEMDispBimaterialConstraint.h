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

#ifndef XFEMDISPBIMATERIALCONSTRAINT_H
#define XFEMDISPBIMATERIALCONSTRAINT_H

// MOOSE includes
#include "ElemElemConstraint.h"
#include "MooseMesh.h"

#include "RankTwoTensor.h"
#include "RankFourTensor.h"

// Forward Declarations
class XFEMDispBimaterialConstraint;
class XFEM;

template <>
InputParameters validParams<XFEMDispBimaterialConstraint>();

class XFEMDispBimaterialConstraint : public ElemElemConstraint
{
public:
  XFEMDispBimaterialConstraint(const InputParameters & parameters);
  virtual ~XFEMDispBimaterialConstraint();

protected:
  virtual void reinitConstraintQuadrature(const ElementPairInfo & element_pair_info) override;

  virtual Real computeQpResidual(Moose::DGResidualType type) override;

  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  const unsigned int _component;

  /// Coupled displacement variables
  unsigned int _ndisp;
  std::vector<const VariableValue *> _disp;
  std::vector<const VariableGradient *> _grad_disp;

  std::vector<MooseVariable *> _disp_vars;

  std::vector<const VariableValue *> _disp_neighbor;
  std::vector<const VariableGradient *> _grad_disp_neighbor;

  Real _E_pos;
  Real _nu_pos;

  Real _E_neg;
  Real _nu_neg;

  RankFourTensor _Cijkl_pos;
  RankFourTensor _Cijkl_neg;

  /// Vector normal to the internal interface
  Point _interface_normal;
  Point _interface_normal_neighbor;

  /// volume fractions of both elements
  Real _elem_vol_frac;
  Real _elem_neighbor_vol_frac;

  /// Stabilization parameter in Nitsche's formulation
  Real _alpha;

  /// Avtive time from-to
  Real _time_from;
  Real _time_to;

  /// The variable number of the level set variable we are operating on
  const unsigned int _level_set_var_number;

  /// system reference
  const System & _system;

  /// the subproblem solution vector
  const NumericVector<Number> * _solution;

  /// use the positive level set region's material properties
  bool _use_positive_property;

  /// Pointer to the XFEM controller object
  std::shared_ptr<XFEM> _xfem;
};

#endif /* XFEMDISPBIMATERIALCONSTRAINT_H */
