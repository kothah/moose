#ifndef HCOUPLED_NEUMANN_BC_H
#define HCOUPLED_NEUMANN_BC_H

#include "IntegratedBC.h"

//Forward declarations
class HCoupledNeumannBC;

template <>
InputParameters validParams<HCoupledNeumannBC>();

// implementation of a coupled Neumann BC where grad(u) = alpha * v on the boundary
class HCoupledNeumannBC : public IntegratedBC{
    public:
        // factory constructor, takes parameters so that all declared classes
        // can be built using the same constructor
        HCoupledNeumannBC (const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;

    private:
        // multiplier on the boundary
        Real _alpha;

        // holds the values at the quadrature points of a coupled variable
        const VariableValue & _hardik_var_value;
};
#endif //HCOUPLED_NEUMANN_BC_H
