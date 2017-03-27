#include "HCoupledNeumannBC.h"

template <>
InputParameters
validParams<HCoupledNeumannBC>()
{
    InputParameters params = validParams<IntegratedBC>();

    // adding parameter that will be extracted from the input file by the parser
    params.addParam<Real>("alpha",1.0,"Value multiplied by the coupled value on the boundary");
    params.addRequiredCoupledVar("some_var","Flux Value at the boundary");
    return params;
}

HCoupledNeumannBC::HCoupledNeumannBC(const InputParameters & parameters)
    : IntegratedBC(parameters),
    _alpha(getParam<Real>("alpha")),
    _hardik_var_value(coupledValue("some_var"))
{
}

Real HCoupledNeumannBC::computeQpResidual(){
    return -_test[_i][_qp] * _alpha * _hardik_var_value[_qp];
}
