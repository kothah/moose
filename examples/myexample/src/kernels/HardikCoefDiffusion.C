#include "HardikCoefDiffusion.h"

template <>
InputParameters
validParams<HardikCoefDiffusion>(){
    InputParameters params = validParams<Kernel>();
    params.set<Real>("coef") = 0.0;
    return params;
}
HardikCoefDiffusion::HardikCoefDiffusion(const InputParameters & parameters)
    : Kernel (parameters), _coef(getParam<Real>("coef")){
}

Real HardikCoefDiffusion::computeQpResidual(){
    return _coef * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real HardikCoefDiffusion::computeQpJacobian(){
    return _coef * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
