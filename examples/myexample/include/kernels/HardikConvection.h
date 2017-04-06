#ifndef HARDIK_CONVECTION_H
#define HARDIK_CONVECTION_H

#include "Kernel.h"

// Forward declaration
class HardikConvection;

template <>
InputParameters validParams <HardikConvection>();

class HardikConvection : public Kernel{
    public:
        // the constructor declaration
        // class takes a string and a InputParameters object, just like other Kernel-derived classes
        HardikConvection(const InputParameters & parameters);
    protected:
        // Responsible for computing the residual at one quadrature point.
        // function should always be defined in the .C file.
        virtual Real computeQpResidual() override;

        // Responsible for computing the diagonal block of the preconditioning matrix.
        // essentially the partial derivative of the residual with respect to the variable this kernel operates on ("u")
        // Note that this can be an approximation or linearization
        // In this case it's not because the Jacobian of this operator is easy to calculate.
        // This function should always be defined in the .C file.
        virtual Real computeQpJacobian() override;

    private:
        // A vector object for stoing velocity.  Convenient for dot products.
        RealVectorValue _velocity;
};

#endif //HARDIK_CONVECTION_H
