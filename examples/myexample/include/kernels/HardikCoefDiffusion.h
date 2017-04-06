#ifndef HARDIK_COEF_DIFFUSION_H
#define HARDIK_COEF_DIFFUSION_H

#include "Kernel.h"

//Forward declaration
class HardikCoefDiffusion;

template <>
InputParameters validParams<HardikCoefDiffusion>();

class HardikCoefDiffusion : public Kernel{
    public:
        HardikCoefDiffusion (const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;
        virtual Real computeQpJacobian() override;

    private:
        Real _coef;
};

#endif //HARDIK_COEFF_DIFFUSION_H
