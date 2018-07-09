/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef PFCUTUSEROBJECT_H
#define PFCUTUSEROBJECT_H

#include "GeometricCutUserObject.h"

// Forward declarations
class PFCutUserObject;

registerMooseObject("XFEMApp", PFCutUserObject);

template <>
InputParameters validParams<PFCutUserObject>();

class PFCutUserObject : public GeometricCutUserObject
{
public:
  PFCutUserObject(const InputParameters & parameters);

  virtual bool cutElementByGeometry(const Elem * elem,
                                    std::vector<Xfem::CutEdge> & cut_edges,
                                    std::vector<Xfem::CutNode> & cut_nodes,
                                    Real time) const override;
  virtual bool cutElementByGeometry(const Elem * elem,
                                    std::vector<Xfem::CutFace> & cut_faces,
                                    Real time) const override;

  virtual bool cutFragmentByGeometry(std::vector<std::vector<Point>> & frag_edges,
                                     std::vector<Xfem::CutEdge> & cut_edges,
                                     Real time) const override;
  virtual bool cutFragmentByGeometry(std::vector<std::vector<Point>> & frag_faces,
                                     std::vector<Xfem::CutFace> & cut_faces,
                                     Real time) const override;

  virtual const std::vector<Point>
  getCrackFrontPoints(unsigned int num_crack_front_points) const override;

protected:
  /// The variable number of the phase field variable we using to define the cuts
  const unsigned int _pf_var_number;

  /// system reference
  const System & _system;

  /// the subproblem solution vector
  const NumericVector<Number> * _solution;
};

#endif // LEVELSETCUTUSEROBJECT_H
