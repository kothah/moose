#include "HCoupledDirichletBC.h"

template <>
InputParameters
validParams<HCoupledDirichletBC>(){
    InputParameters params = validParams<NodalBC>();

    // adding a parameter that will be extracted from the input file by the Parser
    params.addParam<Real> ("alpha", 1.0, "Value multiplied by the coupled value on the boundary");
    params.addRequiredCoupledVar("some_var","Value on the Boundary");
    return params;
}

HCoupledDirichletBC::HCoupledDirichletBC(const InputParameters & parameters)
    :NodalBC(parameters),
    // grab teh parameter of multiplier
    _alpha(getParam<Real>("alpha")),

    //Get the reference to the coupled variable's values.
    _hardik_var_value(coupledValue("some_var"))
{
}

Real HCoupledDirichletBC::computeQpResidual(){
    return _u[_qp] - (_alpha * _hardik_var_value[_qp]);
}
