[GlobalParams]
  order = FIRST
  family = LAGRANGE
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 30
  ny = 30
  xmin = 0.0
  xmax = 10.0
  ymin = 0.0
  ymax = 10.0
  elem_type = QUAD4
[]

[XFEM]
  geometric_cut_userobjects = 'line_seg_cut_uo1 line_seg_cut_uo2 line_seg_cut_uo3 line_seg_cut_uo4
  line_seg_cut_uo5 line_seg_cut_uo6'
  qrule = volfrac
  output_cut_plane = true
[]

[UserObjects]
  [./line_seg_cut_uo1]
    type = LineSegmentCutUserObject
    cut_data = '1.5 5.0 3.0 1.5'
  [../]
  [./line_seg_cut_uo2]
    type = LineSegmentCutUserObject
    cut_data = '3.0 1.5 7.0 1.5'
  [../]
  [./line_seg_cut_uo3]
    type = LineSegmentCutUserObject
    cut_data = '7.0 1.5 8.5 5.0'
  [../]
  [./line_seg_cut_uo4]
    type = LineSegmentCutUserObject
    cut_data = '8.5 5.0 7.0 8.5'
  [../]
  [./line_seg_cut_uo5]
    type = LineSegmentCutUserObject
    cut_data = '7.0 8.5 3.0 8.5'
  [../]
  [./line_seg_cut_uo6]
    type = LineSegmentCutUserObject
    cut_data = '3.0 8.5 1.5 5.0'
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./force]
    type = ParsedFunction
    value = '-0.02*x*(x-10) - 0.02*y*(y-10)'
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
    gamma = 0.0001
    alpha = 15
  [../]
[]

[BCs]
# Define boundary conditions
  [./left_u]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  [../]

  [./right_u]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
  [./top_u]
    type = DirichletBC
    variable = u
    boundary = top
    value = 1
  [../]

  [./bottom_u]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 1
  [../]
[]

[Executioner]
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

  start_time = 0.0
  dt = 0.5
  end_time = 1.0
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
