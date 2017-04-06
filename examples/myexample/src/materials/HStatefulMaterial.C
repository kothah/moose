#include "HStatefulMaterial.h"

template<>
InputParameters
validParams <HStatefulMaterial>()
{
    InputParameters params = validParams <Material>();
    params.addParam<Real>("initial_diffusivity",1.0,"The initial diffusivity");
    return params;
}

HStatefulMaterial::HStatefulMaterial( const InputParameters & parameters)
    :Material(parameters),

    // get a parameter value fo the diffusivity
    _initial_diffusivity(getParam<Real>("initial_diffusivity")),

    // declare that the material is going to have a Real valued property named 
    // "diffusivity" that kernel an use
    _diffusivity(declareProperty<Real>("diffusivity")),

    // retrive an old value of diffusivity
    // Note: this is _expensive_ as we have to store values for each
    // qp throughout the mesh. Only do this if you REALLY need it!
    _diffusivity_old(getMaterialPropertyOld<Real>("diffusivity"))
{
}

void HStatefulMaterial::initQpStatefulProperties(){
    // init the diffusivity property
    // (this will become old_diffusivity in the first call of computeProperties)
    _diffusivity[_qp] = _initial_diffusivity;
}

void HStatefulMaterial::computeQpProperties(){
    _diffusivity[_qp] = _diffusivity_old[_qp] *2 ;
}
