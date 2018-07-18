# XFEM and Nitsche contact, the body is cut in two parts and then it comes # back in "self" contact

[GlobalParams]
  order = FIRST
  family = LAGRANGE

  displacements = 'disp_x disp_y'
  volumetric_locking_correction = false
[]

[XFEM]
  geometric_cut_userobjects = 'line_seg_cut_uo'
  qrule = moment_fitting #volfrac
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
    type = LevelSetCutUserObject
    level_set_var = ls
  [../]
[]

[Kernels]
  [./TensorMechanics]
  [../]
[]

[Functions]
  [./ls_func]
    type = ParsedFunction
    value = 'y-0.5'
  [../]
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
    type = XFEMDispTimeConstraint
    variable = disp_x
    component=0
    E=1e6
    nu=0.3
    time_from=0.5
    time_to=2
    alpha = 1.0e10
    use_displaced_mesh = false
   # level_set_var = ls 
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
  [./disp_y]
    type = XFEMDispTimeConstraint
    variable = disp_y
    component=1
    E=1e6
    nu=0.3
    time_from=0.5
    time_to=2
    alpha = 1.0e10
    #level_set_var = ls 
    use_displaced_mesh =false
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
[]

[AuxVariables]
  [./ls]
    order = FIRST
    family = LAGRANGE
  [../]
  [./vmstress]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_max]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_mid]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_min]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./ls_function]
    type = FunctionAux
    variable = ls
    function = ls_func
  [../]
  [./vmstress]
    type = RankTwoScalarAux
    rank_two_tensor = total_strain
    variable = vmstress
    scalar_type = VonMisesStress
    execute_on = timestep_end
  [../]
    [./stress_max]
    type = RankTwoScalarAux
    rank_two_tensor = stress
    variable = stress_max
    scalar_type = MaxPrincipal
  [../]
  [./stress_mid]
    type = RankTwoScalarAux
    rank_two_tensor = stress
    variable = stress_mid
    scalar_type = MidPrincipal
  [../]
  [./stress_min]
    type = RankTwoScalarAux
    rank_two_tensor = stress
    variable = stress_min
    scalar_type = MinPrincipal
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

[Preconditioning]
  [./smp]
    type = SMP
    full = true
 [../]
[]

[Executioner]
  type = Transient

  solve_type = 'NEWTON'
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
  petsc_options_value = '201                hypre    boomeramg      30'
  #petsc_options_iname = '-pc_type -pc_factor_mat_solver_package -ksp_type'
  #petsc_options_value = ' lu       mumps         preonly' 
  #line_search = 'none'

#  [./Predictor]
#    type = SimplePredictor
#    scale = 1.0
#  [../]

# controls for linear iterations
  l_max_its = 100
  l_tol = 1e-8

# controls for nonlinear iterations
  nl_abs_tol = 1e-10

# time control
  start_time = 0.0
  dt = 0.1
  end_time = 1.3
  num_steps = 5000

  max_xfem_update = 1
[]

[Outputs]
  exodus = true
  execute_on = timestep_end
  [./console]
    type = Console
    #perf_log = true
    output_linear = true
  [../]
[]
