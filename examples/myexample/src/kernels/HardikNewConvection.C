#include "HardikNewConvection.h"
// valid parameters for the kernel and default values

template <>
InputParameters
validParams<HardikNewConvection>(){
    InputParameters params= validParams<Kernel>();
    return params;
}

// Retrieve a gradient material property to use for the convection
// velocity
HardikNewConvection::HardikNewConvection(const InputParameters & parameters)
    : Kernel (parameters),
    _velocity(getMaterialProperty<RealGradient>("convection_velocity"))
{
}

Real HardikNewConvection::computeQpResidual()
{
    // velocity * _gradu in weak form
    return _test[_i][_qp] * (_velocity[_qp] * _grad_u[_qp]);
}

Real HardikNewConvection::computeQpJacobian(){
    // the partial derivative of _grad_u is _grad_phi
    return _test[_i][_qp] * (_velocity[_qp] * _grad_phi[_j][_qp]);
}
