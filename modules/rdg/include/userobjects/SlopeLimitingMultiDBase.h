//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SLOPELIMITINGMULTIDBASE_H
#define SLOPELIMITINGMULTIDBASE_H

#include "SlopeLimitingBase.h"
#include "SlopeReconstructionBase.h"

class SlopeLimitingMultiDBase;

template <>
InputParameters validParams<SlopeLimitingMultiDBase>();

/**
 * Base class for multi-dimensional slope limiting to limit
 * the slopes of cell average variables
 */
class SlopeLimitingMultiDBase : public SlopeLimitingBase
{
public:
  SlopeLimitingMultiDBase(const InputParameters & parameters);

protected:
  /// slope reconstruction user object
  const SlopeReconstructionBase & _rslope;
};

#endif
