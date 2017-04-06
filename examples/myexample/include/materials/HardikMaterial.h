#ifndef HARDIK_MATERIAL_H
#define HARDIK_MATERIAL_H

#include "Material.h"
#include "LinearInterpolation.h"

class HardikMaterial;

template <> InputParameters validParams<HardikMaterial>();

// Example material class which defines few properties

class HardikMaterial : public Material{
    public:
        HardikMaterial (const InputParameters & parameters);
    
    protected:
        virtual void computeQpProperties() override;
    private:
        // this memeber will hold the compute values for real value property
        MaterialProperty<Real> & _diffusivity;

        // compute the gradient value property
        MaterialProperty<RealGradient> & _convection_velocity;

        // gradient of the coupled variable
        const VariableGradient & _diffusion_gradient;

        //retunrs piecewise linear function based on a series of points
        //and the corresponding values
        LinearInterpolation _piecewise_func;
};

#endif//HARDIK_MATERIAL_H
