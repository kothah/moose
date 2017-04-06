#include "HardikDiffusion.h"

template <>
InputParameters
validParams<HardikDiffusion>(){
    InputParameters params = validParams<Kernel>();
    params.addClassDescription("The laplacian operator (\nabla \cdot \nambla u) with weak form");
    return params;
}

HardikDiffusion::HardikDiffusion(const InputParameters & parameters): Kernel (parameters){}

Real HardikDiffusion::computeQpResidual(){
    return _grad_u[_qp]* _grad_test[_i][_qp];
}
Real HardikDiffusion::computeQpJacobian(){
    return _grad_phi[_j][_qp]* _grad_test[_i][_qp];
}





