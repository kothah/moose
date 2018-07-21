

[GlobalParams]
  order = FIRST
  family = LAGRANGE

  displacements = 'disp_x disp_y'
  volumetric_locking_correction = false
[]

[XFEM]
  geometric_cut_userobjects = 'level_set_cut_uo'
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
  nx = 251
  ny = 251
  xmin = -1.7
  xmax = 1.7
  ymin = -1.7
  ymax = 1.7
  elem_type = QUAD4
[]

[UserObjects]
  [./level_set_cut_uo]
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
    #value = 'y-0.51'
    #value = 'sqrt((y-.5)*(y-.5) + (x-.5)*(x-.5)) - 0.3'
    value='(cos(x*x)+sin(y*y))*(sin(x*x)+cos(y*y))-1.0'
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
  [./dispx_constraint]
    type = XFEMDispGluedConstraint
    use_displaced_mesh = false
    variable = disp_x
    component=0
    alpha = 1e10
    E_pos=1e6
    nu_pos=0.3
    E_neg=1e7
    nu_neg=0.3
    geometric_cut_userobject = 'level_set_cut_uo'
    level_set_var = ls
  [../]
  [./dispy_constraint]
    type = XFEMDispGluedConstraint
    use_displaced_mesh = false
    variable = disp_y
    alpha = 1e10
    component=1
    E_pos=1e6
    nu_pos=0.3
    E_neg=1e7
    nu_neg=0.3
    geometric_cut_userobject = 'level_set_cut_uo'
    level_set_var = ls
  [../]
[]

[AuxVariables]
  [./ls]    order = FIRST    family = LAGRANGE  [../]

  [./stress_xx]    order = CONSTANT    family = MONOMIAL  [../]
  [./stress_yy]    order = CONSTANT    family = MONOMIAL  [../]
  [./stress_xy]    order = CONSTANT    family = MONOMIAL  [../]

  [./a_strain_xx]    order = CONSTANT    family = MONOMIAL  [../]
  [./a_strain_yy]    order = CONSTANT    family = MONOMIAL  [../]
  [./a_strain_xy]    order = CONSTANT    family = MONOMIAL  [../]
  [./b_strain_xx]    order = CONSTANT    family = MONOMIAL  [../]
  [./b_strain_yy]    order = CONSTANT    family = MONOMIAL  [../]
  [./b_strain_xy]    order = CONSTANT    family = MONOMIAL  [../]


  [./a_vmstress]    order = CONSTANT    family = MONOMIAL  [../]
  [./b_vmstress]    order = CONSTANT    family = MONOMIAL  [../]

  [./stress_max]    order = CONSTANT    family = MONOMIAL  [../]
  [./stress_mid]    order = CONSTANT    family = MONOMIAL  [../]
  [./stress_min]    order = CONSTANT    family = MONOMIAL  [../]
[]

[AuxKernels]
  [./ls_function]
    type = FunctionAux
    variable = ls
    function = ls_func
  [../]
  [./stress_xx]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 0     index_j = 0
    variable = stress_xx
  [../]
  [./stress_yy]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 1    index_j = 1
    variable = stress_yy
  [../]
  [./stress_xy]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 0    index_j = 1
    variable = stress_xy
  [../]
  [./a_strain_xx]
    type = RankTwoAux
    rank_two_tensor = A_total_strain
    index_i = 0    index_j = 0
    variable = a_strain_xx
  [../]
  [./a_strain_yy]
    type = RankTwoAux
    rank_two_tensor = A_total_strain
    index_i = 1    index_j = 1
    variable = a_strain_yy
  [../]
  [./a_strain_xy]
    type = RankTwoAux
    rank_two_tensor = A_total_strain
    index_i = 0    index_j = 1
    variable = a_strain_xy
  [../]
  [./b_strain_xx]
    type = RankTwoAux
    rank_two_tensor = B_total_strain
    index_i = 0    index_j = 0
    variable = b_strain_xx
  [../]
  [./b_strain_yy]
    type = RankTwoAux
    rank_two_tensor = B_total_strain
    index_i = 1    index_j = 1
    variable = b_strain_yy
  [../]
  [./b_strain_xy]
    type = RankTwoAux
    rank_two_tensor = B_total_strain
    index_i = 0    index_j = 1
    variable = b_strain_xy
  [../]
  [./a_vmstress]
    type = RankTwoScalarAux
    rank_two_tensor = A_total_strain
    variable = a_vmstress
    scalar_type = VonMisesStress
    execute_on = timestep_end
  [../]
  [./b_vmstress]
    type = RankTwoScalarAux
    rank_two_tensor = B_total_strain
    variable = b_vmstress
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
  [./elasticity_tensor_A]
    type = ComputeIsotropicElasticityTensor
    base_name = A
    youngs_modulus = 1e6
    poissons_ratio = 0.3
  [../]
  [./strain_A]
    type = ComputeSmallStrain
    base_name = A
  [../]
  [./stress_A]
    type = ComputeLinearElasticStress
    base_name = A
  [../]
  [./elasticity_tensor_B]
    type = ComputeIsotropicElasticityTensor
    base_name = B
    youngs_modulus = 1e7
    poissons_ratio = 0.3
  [../]
  [./strain_B]
    type = ComputeSmallStrain
    base_name = B
  [../]
  [./stress_B]
    type = ComputeLinearElasticStress
    base_name = B
  [../]
  [./combined]
    type = LevelSetBiMaterialStress
    levelset_positive_base = 'A'
    levelset_negative_base = 'B'
    level_set_var = ls
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

  [./Predictor]
    type = SimplePredictor
    scale = 1.0
  [../]

# controls for linear iterations
  l_max_its = 100
  l_tol = 1e-10

# controls for nonlinear iterations
  nl_max_its = 50
  nl_abs_tol = 1e-6

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
    #perf_log = true
    output_linear = true
  [../]
[]
