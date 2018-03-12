#ifndef VECTORCURLPENALTYDIRICHLETBC_H
#define VECTORCURLPENALTYDIRICHLETBC_H

#include "VectorIntegratedBC.h"

class VectorCurlPenaltyDirichletBC;

template <>
InputParameters validParams<VectorCurlPenaltyDirichletBC>();

class VectorCurlPenaltyDirichletBC : public VectorIntegratedBC
{
public:
  VectorCurlPenaltyDirichletBC(const InputParameters & parameters);

protected:
  Real _penalty;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  Function & _exact_x;
  Function & _exact_y;
  Function & _exact_z;
};

#endif // VECTORCURLPENALTYDIRICHLETBC_H
