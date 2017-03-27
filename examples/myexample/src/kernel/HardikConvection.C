#include "HardikConvection.h"
// valid parameters for the kernel and default values

template <>
InputParameters
validParams<HardikConvection>(){
    InputParameters params= validParams<Kernel>();
    params.addRequiredParam<RealVectorValue>("velocity","velocity vector");
    return params;
}

HardikConvection::HardikConvection(const InputParameters & parameters)
    : Kernel (parameters), _velocity(getParam<RealVectorValue>("velocity"))
{
}

Real HardikConvection::computeQpResidual()
{
    // velocity * _gradu in weak form
    return _test[_i][_qp] * (_velocity * _grad_u[_qp]);
}

Real HardikConvection::computeQpJacobian(){
    // the partial derivative of _grad_u is _grad_phi
    return _test[_i][_qp] * (_velocity * _grad_phi[_j][_qp]);
}
