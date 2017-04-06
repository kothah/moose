#ifndef HARDIK_DIFFUSION_H
#define HARDIK_DIFFUSION_H

#include "Kernel.h"

class HardikDiffusion;

template <>
InputParameters validParams <HardikDiffusion>();

//This kernel impliments the lapacian operator
// \nabla u \cdot \namba \phi_i

class HardikDiffusion : public Kernel{
    public:
        HardikDiffusion(const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;
        virtual Real computeQpJacobian() override;

        const MaterialProperty<Real> & _diffusivity;
};

#endif //HARDIK_DIFFUSION_H
