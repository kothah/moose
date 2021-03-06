//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ClampTestFunction.h"

#include "MathUtils.h"

registerMooseObject("MooseTestApp", ClampTestFunction);

template <>
InputParameters
validParams<ClampTestFunction>()
{
  return validParams<Function>();
}

ClampTestFunction::ClampTestFunction(const InputParameters & parameters) : Function(parameters) {}

Real
ClampTestFunction::value(Real /*t*/, const Point & p)
{
  return MathUtils::clamp<Real>(p(0), 0.2, 0.8);
}
