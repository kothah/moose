#ifndef HCOUPLED_DIRICHLET_BC_H
#define HCOUPLED_DIRICHLET_BC_H

#include "NodalBC.h"

//Forward declarations
class HCoupledDirichletBC;

template <>
InputParameters validParams<HCoupledDirichletBC>();

// implementation of a coupled Dirichlet BC whre u= alpha*some_var on the boundary
class HCoupledDirichletBC : public NodalBC{
    public:
        // factory constructor, takes parameters so that all declared classes
        // can be built using the same constructor
        HCoupledDirichletBC (const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;

    private:
        // multiplier on the boundary
        Real _alpha;

        // holds the values at the quadrature points of a coupled variable
        const VariableValue & _hardik_var_value;
};
#endif //HCOUPLED_DIRICHLET_BC_H
