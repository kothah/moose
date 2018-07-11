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

#ifndef XFEMSINGLEVARIABLEINEQCONSTRAINT_H
#define XFEMSINGLEVARIABLEINEQCONSTRAINT_H

// MOOSE includes
#include "ElemElemConstraint.h"
#include "MooseMesh.h"

// Forward Declarations
class XFEMSingleVariableInEqConstraint;

class XFEM;

template <>
InputParameters validParams<XFEMSingleVariableInEqConstraint>();

class XFEMSingleVariableInEqConstraint : public ElemElemConstraint
{
public:
  XFEMSingleVariableInEqConstraint(const InputParameters & parameters);
  virtual ~XFEMSingleVariableInEqConstraint();

protected:
  virtual void reinitConstraintQuadrature(const ElementPairInfo & element_pair_info) override;

  virtual Real computeQpResidual(Moose::DGResidualType type) override;

  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  /// Vector normal to the internal interface
  Point _interface_normal;

  /// Stabilization parameter in Nitsche's formulation
  Real _alpha;

  /// Avtive time from-to
  Real _time_from;
  Real _time_to;

  /// Use penalty formulation
  bool _use_penalty;

  /// Pointer to the XFEM controller object
  std::shared_ptr<XFEM> _xfem;
};

#endif /* XFEMEQUALVALUECONSTRAINT_H_ */
