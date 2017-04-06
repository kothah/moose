#ifndef HARDIK_TIME_DERIVATIVE
#define HARDIK_TIME_DERIVATIVE

#include "TimeDerivative.h"

class HardikTimeDerivative;

template <>
InputParameters validParams <HardikTimeDerivative>();

class HardikTimeDerivative:public TimeDerivative{
    public:
        HardikTimeDerivative (const InputParameters & parameters);

    protected:
        virtual Real computeQpResidual() override;
        virtual Real computeQpJacobian() override;

        Real _time_coefficient;
};


#endif //HARDIK_TIME_DERIVATIVE
