#include "HardikMaterialDiffusion.h"
#include "Material.h"

template <>
InputParameters validParams <HardikMaterialDiffusion>(){
    InputParameters params = validParams<Diffusion>();
    return params;
}

HardikMaterialDiffusion::HardikMaterialDiffusion(const InputParameters & parameters)
    : Diffusion(parameters), _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
}

Real HardikMaterialDiffusion::computeQpResidual(){
    // diffusivity constant 
    return _diffusivity[_qp] * Diffusion::computeQpResidual();
}

Real HardikMaterialDiffusion::computeQpJacobian(){
    // diffusivity constant 
    return _diffusivity[_qp] * Diffusion::computeQpJacobian();
}
