#include "HardikAux.h"

template <>
InputParameters validParams <HardikAux>(){
    InputParameters params = validParams<AuxKernel>();
    params.addParam<Real> ("value",0.0,"Scaled value used for auxiliary calculation");
    params.addRequiredCoupledVar("coupled", "Coupled variable");

    return params;
}

HardikAux::HardikAux(const InputParameters & parameters)
    :AuxKernel(parameters),
    //coupling a value from one of the kernels with a call to coupledValueAux
    _coupled_val(coupledValue("coupled")),

    // setting the memeber scalar value from InputParameters
    _value(getParam<Real>("value"))
{
}

// Auxkernel override computeValue() instead of computeQpResidual().
// Aux variables are caluclated either one per element or one per node
// Elemental - constant monomial
// Nodal - first lagrange
// no changed in the code required
Real HardikAux::computeValue(){
    return _coupled_val[_qp] + _value;
}
