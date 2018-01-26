/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "Circle2DCutUserObject.h"

// MOOSE includes
#include "MooseError.h"

// XFEM includes
#include "XFEMFuncs.h"

template <>
InputParameters
validParams<Circle2DCutUserObject>()
{
  // Get input parameters from parent class
  InputParameters params = validParams<GeometricCut2DCurvesUserObject>();

  // Add required parameters
  params.addRequiredParam<std::vector<Real>>("cut_data",
                                             "Vector of Real values providing cut information");
  // Class description
  params.addClassDescription("Creates a UserObject for circular cuts on 2D meshes for XFEM");
  // Return the parameters
  return params;
}

Circle2DCutUserObject::Circle2DCutUserObject(const InputParameters & parameters)
  : GeometricCut2DCurvesUserObject(parameters), _cut_data(getParam<std::vector<Real>>("cut_data"))
{
  const int cut_data_len = 3;

  // Throw error if length of cut_data is incorrect
  if (_cut_data.size() != cut_data_len)
    mooseError("Length of Circle2DCutUserObject cut_data must be 3");

  // Assign cut_data to vars used to construct cuts
  _center = Point(_cut_data[0], _cut_data[1], 0.0);
  _radius = _cut_data[2];
}
