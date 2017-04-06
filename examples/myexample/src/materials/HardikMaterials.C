#include <HardikMaterial.h>

template <>
InputParameters validParams<HardikMaterial>(){
    InputParameters params = validParams<Material>();

    params.addRequiredParam<std::vector<Real>>(
            "independent_values", "The vector of independent values for building the piecewise function");

    params.addRequiredParam<std::vector<Real>>(
            "dependent_values","The vector of dependent values for building the picewise function");

    params.addCoupledVar(
            "diffusion_gradient","The Gradient of this variable will be use to compute a velocity vector property"  );
    return params;
}

HardikMaterial::HardikMaterial (const InputParameters & parameters): Material(parameters),
    _diffusivity(declareProperty<Real>("diffusivity")),

    _convection_velocity(declareProperty<RealGradient>("convection_velocity")),

    _diffusion_gradient(isCoupled("diffusion_gradient") ? coupledGradient ("diffusion_gradient") : _grad_zero),

    _piecewise_func(getParam<std::vector<Real>> ("independent_values"),
            getParam<std::vector<Real>> ("dependent_values")){

    }

void HardikMaterial::computeQpProperties(){
    _diffusivity[_qp] = _piecewise_func.sample(_q_point[_qp](2));
    _convection_velocity[_qp] = _diffusion_gradient[_qp];
}
