[GlobalParams]
  order = FIRST
  family = LAGRANGE
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 50
  ny = 50
  xmin = -1.2
  xmax = 1.2
  ymin = -1.2
  ymax = 1.2
  elem_type = QUAD4
[]

[XFEM]
  geometric_cut_userobjects = 'cut_uo'
  qrule = volfrac
  output_cut_plane = true
[]

[UserObjects]
 [./cut_uo]
    type = Ellipse2DCutUserObject
    cut_data = '0.0 0.0 1.0 0.7'
  [../]


[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./force]
    type = ParsedFunction
    value = '-(x+1.5)*(x-1.5) - (y+1.5)*(y-1.5)'
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./bodyforce]
    type = BodyForce
    variable = u
    function = force
  [../]
[]

[Constraints]
  [./xfem_constraint]
    type = XFEMSingleVariableBC
    variable = u
    dirichlet = 0
    gamma = 10e-9
    alpha = 9
  [../]
[]

[BCs]
# Define boundary conditions
  [./left_u]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0.25
  [../]

  [./right_u]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0.25
  [../]
  [./top_u]
    type = DirichletBC
    variable = u
    boundary = top
    value = 0.25
  [../]

  [./bottom_u]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 0.25
  [../]
[]

[Executioner]
  [./Quadrature]
    type = GAUSS_LOBATTO
    order = FIFTH
  [../]
  type = Steady
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg' 
#  petsc_options_iname = '-pc_type'
#  petsc_options_value = 'lu'
  
#  petsc_options_iname = '-pc_type -pc_mg_levels -pc_mg_smoothup -pc_mg_smoothdown'
#  petsc_options_value = 'gamg 2 3 3'
  line_search = 'none'

  l_tol = 1e-8
  nl_max_its = 15
  nl_rel_tol = 1e-8
  nl_abs_tol = 1e-8
[]

[Outputs]
  interval = 1
  execute_on = timestep_end
  exodus = true
  [./console]
    type = Console
    #perf_log = true
    output_linear = true
  [../]
[]
