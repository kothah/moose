#include "HardikIC.h"

template <> InputParameters validParams <HardikIC> (){
    InputParameters params = validParams<InitialCondition>();
    params.addRequiredParam<Real>("coefficient", "The value of the initial condition");
    return params;
}

HardikIC::HardikIC(const InputParameters & parameters)
    : InitialCondition(parameters), _coefficient(getParam<Real>("coefficient")){
}

Real HardikIC::value (const Point & p){
    // _value * x
    //  The point class in defined in libmesh.
    //  spatial coordinates can be accessed individually using paranthesis operator
    return 2. * _coefficient * std::abs(p(0));
}
