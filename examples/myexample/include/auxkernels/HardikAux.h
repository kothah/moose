#ifndef HARDIK_AUX_H
#define HARDIK_AUX_H

#include "AuxKernel.h"

class HardikAux;

template <>
InputParameters validParams <HardikAux>();

class HardikAux: public AuxKernel{
    public:
        HardikAux(const InputParameters & parameters);

    protected:
        virtual Real computeValue() override;

        const VariableValue & _coupled_val;

        Real _value;
};

#endif //HARDIK_AUX_H
