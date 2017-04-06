#ifndef HSTATEFUL_MATERIAL_H
#define HSTATEFUL_MATERIAL_H

#include "Material.h"

class HStatefulMaterial;

template <>
InputParameters validParams <HStatefulMaterial>();

class HStatefulMaterial : public Material{
    public:
        HStatefulMaterial (const InputParameters & parameters);

    protected:
        virtual void initQpStatefulProperties() override;
        virtual void computeQpProperties() override;

    private:
        Real _initial_diffusivity;
        // two arrays to hold the current and previous material properties
        MaterialProperty<Real> & _diffusivity;
        const MaterialProperty<Real> & _diffusivity_old;
};

#endif //HSTATEFUL_MATERIAL_H
