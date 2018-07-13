[GlobalParams]
  order = FIRST
  family = LAGRANGE

  displacements = 'disp_x disp_y'
  volumetric_locking_correction = false
[]

[XFEM]
  geometric_cut_userobjects = 'line_seg_cut_uo'
  qrule = volfrac
  output_cut_plane = true
[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
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

[Kernels]
  [./TensorMechanics]
  [../]
[]

[Functions]
  [./push]
    type = ParsedFunction
    value = 0.05*(0.5-(5*(t-0.5)/4))
  [../]
  [./pull]
    type = ParsedFunction
    value = 0.05*t
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
  [./topy_push]
    type = FunctionPresetBC
    boundary = top
    variable = disp_y
    function = push
  [../]
[]

[Postprocessors]
  [./nonlinear_its]
    type = NumNonlinearIterations
    execute_on = timestep_end
  [../]
[]

[Constraints]
  [./disp_x]
    type = XFEMDispConstraint
    variable = disp_x
    component=0
    time_from=0.5
    time_to=1.2
    disp_x=disp_x
    disp_y=disp_y
    use_penalty = true
    alpha = 1.0e8
    use_displaced_mesh = false
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
  [./disp_y]
    type = XFEMDispConstraint
    variable = disp_y
    component=1
    time_from=0.5
    time_to=1.2
    disp_x=disp_x
    disp_y=disp_y
    use_penalty = true
    alpha = 1.0e8
    use_displaced_mesh =false
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
[]

[Controls]
  [./period1]
    type = TimePeriod
    disable_objects = 'BCs::topy_push'
    start_time = '0'
    end_time = '0.5'
    execute_on = 'initial timestep_begin'
  [../]

  [./period2]
    type = TimePeriod
    disable_objects = 'BCs::topy_pull'
    enable_objects = 'BCs::topy_push'
    start_time = '0.51'
    execute_on = 'initial timestep_begin'
  [../]
[]


[Materials]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 1e6
    poissons_ratio = 0.3
  [../]
  [./stress]
    type = ComputeLinearElasticStress
  [../]
  [./strain]
    type = ComputeSmallStrain
  [../]
[]

[Executioner]
  type = Transient

  solve_type = 'PJFNK'
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
  petsc_options_value = '201                hypre    boomeramg      30'

  line_search = 'none'

  [./Predictor]
    type = SimplePredictor
    scale = 1.0
  [../]

# controls for linear iterations
  l_max_its = 100
  l_tol = 1e-2

# controls for nonlinear iterations
  nl_max_its = 50
  nl_rel_tol = 1e-7
  nl_abs_tol = 1e-7

# time control
  start_time = 0.0
  dt = 0.1
  end_time = 1.2
  num_steps = 5000

  max_xfem_update = 1
[]

[Outputs]
  exodus = true
  execute_on = timestep_end
  [./console]
    type = Console
    perf_log = true
    output_linear = true
  [../]
[]
