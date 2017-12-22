/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef XFEMEQUALVALUEBC_H
#define XFEMEQUALVALUEBC_H

// MOOSE includes
#include "ElemElemConstraint.h"
#include "MooseMesh.h"

// Forward Declarations
class XFEMSingleVariableBC;

template <>
InputParameters validParams<XFEMSingleVariableBC>();

class XFEMSingleVariableBC : public ElemElemConstraint
{
public:
  XFEMSingleVariableBC(const InputParameters & parameters);
  virtual ~XFEMSingleVariableBC();

protected:
  /**
   * Set information needed for constraint integration
   */
  virtual void reinitConstraintQuadrature(const ElementPairInfo & element_pair_info);

  /**
   *  Compute the residual for one of the constraint quadrature points.
   */
  virtual Real computeQpResidual(Moose::DGResidualType type);

  /**
   *  Compute the Jacobian for one of the constraint quadrature points.
   */
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  /// Vector normal to the internal interface
  Point _interface_normal;

  Real _elem1_vol_frac;
  Real _elem2_vol_frac;

  /// Stabilization parameter in Nitsche's formulation
  Real _alpha;
  Real _gamma;

  /// Vector normal to the internal interface
  Real _dirichlet;

  /// Vector normal to the internal interface
  Real _neumann;
};

#endif /* XFEMEQUALVALUECONSTRAINT_H_ */
