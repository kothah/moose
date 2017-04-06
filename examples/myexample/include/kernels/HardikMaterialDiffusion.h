#ifndef HARDIK_MATERIAL_DIFFUSION_H
#define HARDIK_MATERIAL_DIFFUSION_H

#include "Diffusion.h"

class HardikMaterialDiffusion;

template <>
InputParameters validParams <HardikMaterialDiffusion>();

class HardikMaterialDiffusion :public Diffusion{
    public:
        HardikMaterialDiffusion(const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;
        virtual Real computeQpJacobian() override;

        // this will hold ther reference for the material property
        const MaterialProperty<Real> & _diffusivity;
};

#endif // HARDIK_MATERIAL_DIFFUSION_H
