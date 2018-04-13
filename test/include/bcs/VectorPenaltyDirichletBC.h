//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef VECTORPENALTYDIRICHLETBC_H
#define VECTORPENALTYDIRICHLETBC_H

#include "VectorIntegratedBC.h"

class VectorPenaltyDirichletBC;

template <>
InputParameters validParams<VectorPenaltyDirichletBC>();

class VectorPenaltyDirichletBC : public VectorIntegratedBC
{
public:
  VectorPenaltyDirichletBC(const InputParameters & parameters);

protected:
  Real _penalty;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  Function & _exact_x;
  Function & _exact_y;
  Function & _exact_z;
  const bool _linear;
};

#endif // VECTORPENALTYDIRICHLETBC_H
