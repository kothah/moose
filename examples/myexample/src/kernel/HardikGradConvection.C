#include "HardikGradConvection.h"

// valid parameters for the kernel and default values

template <>
InputParameters
validParams<HardikGradConvection>(){
    InputParameters params= validParams<Kernel>();
    params.addRequiredCoupledVar("grad_variable","The gradient of this variable will be used as the velocity vector");
    return params;
}

HardikGradConvection::HardikGradConvection(const InputParameters & parameters)
    : Kernel (parameters), _grad_velocity(coupledGradient("grad_variable"))
{
}

Real HardikGradConvection::computeQpResidual()
{
    // _grad_velocity * _gradu in weak form
    return _test[_i][_qp] * (_grad_velocity[_qp] * _grad_u[_qp]);
}

Real HardikGradConvection::computeQpJacobian(){
    // the partial derivative of _grad_u is _grad_phi
    return _test[_i][_qp] * (_grad_velocity[_qp] * _grad_phi[_j][_qp]);
}
