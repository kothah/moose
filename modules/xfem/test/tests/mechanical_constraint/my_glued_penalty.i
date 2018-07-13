[GlobalParams]
  displacements = 'disp_x disp_y'
  volumetric_locking_correction = true
[]

[XFEM]
  geometric_cut_userobjects = 'line_seg_cut_uo'
  qrule = moment_fitting
  output_cut_plane = true
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 31
  ny = 31
  xmin = 0.0
  xmax = 1.0
  ymin = 0.0
  ymax = 1.0
  elem_type = QUAD4
[]

[UserObjects]
  [./line_seg_cut_uo]
    type = LineSegmentCutUserObject
    cut_data = '1.0  0.5  0.0  0.5'
    time_start_cut = 0.0
    time_end_cut = 0.0
  [../]
[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[Modules/TensorMechanics/Master/All]
  strain = SMALL
  add_variables = true
[]

[Functions]
  [./push]
    type = ParsedFunction
    value = 0.09*(0.5-(5*(t-0.5)/4))
  [../]
  [./pull]
    type = ParsedFunction
    value = -0.01*t
  [../]
[]


[BCs]
  [./bottomx]
    type = PresetBC
    boundary = bottom
    variable = disp_x
    value = 0.0
  [../]
  [./bottomy]
    type = PresetBC
    boundary = bottom
    variable = disp_y
    value = 0.0
  [../]
  [./topx]
    type = PresetBC
    boundary = top
    variable = disp_x
    value = 0.0
  [../]
  [./topy_pull]
    type = FunctionPresetBC
    boundary = top
    variable = disp_y
    function = pull
  [../]
#  [./topy_push]
#    type = FunctionPresetBC
#    boundary = top
#    variable = disp_y
#    function = push
#  [../]
[]

[Constraints]
  [./disp_x]
    type = XFEMDispConstraint
    variable = disp_x
    component = 0
    use_penalty = true
    alpha = 0.5e6
    time_from = 0.5 
    time_to = 2
    use_displaced_mesh = true
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
  [./disp_y]
    type = XFEMDispConstraint
    variable = disp_y
    component = 1
    use_penalty = true
    alpha = 0.5e6
    time_from = 0.5
    time_to = 2
    use_displaced_mesh = true
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeElasticityTensor
    fill_method = symmetric9
    #reading C_11  C_12  C_13  C_22  C_23  C_33  C_44  C_55  C_66
    C_ijkl ='1.0e6  0.0   0.0 1.0e6  0.0  1.0e6 0.5e6 0.5e6 0.5e6'
  [../]
  [./stress]
    type = ComputeLinearElasticStress
  [../]
[]

#[Controls]
#  [./period1]
#    type = TimePeriod
#    disable_objects = 'BCs::topy_push'
#    start_time = '0'
#    end_time = '0.5'
#    execute_on = 'initial timestep_begin'
#  [../]
#  [./period2]
#    type = TimePeriod
#    disable_objects = 'BCs::topy_pull'
#    enable_objects = 'BCs::topy_push'
#    start_time = '0.51'
#    execute_on = 'initial timestep_begin'
#  [../]
#[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'# -ksp_type
  petsc_options_value = 'lu       superlu_dist'#  preonly

  line_search = 'none'

  l_max_its = 100
  nl_max_its = 1000

  l_tol = 1e-6
  nl_rel_tol = 1e-8
  nl_abs_tol = 1e-8
 
# [./Predictor]
#    type = SimplePredictor
#    scale = 1.0
#  [../]

# time control
  start_time = 0.0
  dt = 0.1
  end_time = 1.2
  num_steps = 5000

  max_xfem_update = 1
[]

[Outputs]
  exodus = true
  execute_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_linear = true
  [../]
[]
