#include "HardikTimeDerivative.h"

#include "Material.h"

template <>
InputParameters
validParams <HardikTimeDerivative>(){
    InputParameters params = validParams <TimeDerivative> ();
    params.addParam<Real>("time_coefficient",1.0,"Time Coefficient");
    return params;
}

HardikTimeDerivative::HardikTimeDerivative(const InputParameters & parameters)
    :TimeDerivative(parameters),
    _time_coefficient(getParam<Real>("time_coefficient"))
{

}

Real HardikTimeDerivative::computeQpResidual(){
    return _time_coefficient * TimeDerivative::computeQpResidual();
}

Real HardikTimeDerivative::computeQpJacobian(){
    return _time_coefficient * TimeDerivative::computeQpJacobian();
}
