#This input uses PhaseField-Nonconserved Action to add phase field fracture bulk rate kernels
[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 51
  ny = 25
  ymax = 0.5
[]

[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Modules]
  [./PhaseField]
    [./Nonconserved]
      [./c]
        free_energy = E_el
        kappa = kappa_op
        mobility = L
      [../]
    [../]
  [../]
  [./TensorMechanics]
    [./Master]
      [./mech]
        add_variables = true
        strain = SMALL
        additional_generate_output = 'stress_yy'
        save_in = 'resid_x resid_y'
      [../]
    [../]
  [../]
[]

[XFEM]
  geometric_cut_userobjects = 'pf_marker_uo'
  qrule = moment_fitting
  output_cut_plane = true
[]

[UserObjects]
   [./line_seg_cut_uo]
    type = LineSegmentCutUserObject
    cut_data = '0.5 0.0 0.5 0.2'
    time_start_cut = 0.0
    time_end_cut = 0.0
  [../]
  [./pf_marker_uo]
    type = PFCutUserObject
    pf_var = c
  [../]

[]

[AuxVariables]
  [./resid_x]
  [../]
  [./resid_y]
  [../]
 [./stress_max]
    order = CONSTANT
    family = MONOMIAL
[../]
[]

[AuxKernels]
[./stress_max]
    type = RankTwoScalarAux
    rank_two_tensor = stress
    variable = stress_max
    scalar_type = MaxPrincipal
[../]
[]

[Kernels]
  [./solid_x]
    type = PhaseFieldFractureMechanicsOffDiag
    variable = disp_x
    component = 0
    c = c
  [../]
  [./solid_y]
    type = PhaseFieldFractureMechanicsOffDiag
    variable = disp_y
    component = 1
    c = c
  [../]
[]

[BCs]
  [./xleft_tensile]
    type = FunctionPresetBC
    variable = disp_x
    boundary = left
    function = '-t'
  [../]
  [./xleft_compressive]
    type = FunctionPresetBC
    variable = disp_x
    boundary = left
    function = '4*t'
  [../]
  [./yleft]
    type = PresetBC
    variable = disp_y
    boundary = left
    value = 0
  [../]
  [./xright]
    type = PresetBC
    variable = disp_x
    boundary = right
    value = 0
  [../]
  [./yright]
    type = PresetBC
    variable = disp_y
    boundary = left
    value = 0
  [../]
[]

[Controls]
  [./period1]
    type = TimePeriod
    disable_objects = 'BCs::xleft_compressive'
    start_time = '0'
    end_time = '0.006'
    execute_on = 'initial timestep_begin'
  [../]

  [./period2]
    type = TimePeriod
    disable_objects = 'BCs::xleft_tensile'
    enable_objects = 'BCs::xleft_compressive'
    start_time = '0.00601'
    end_time = '0.01'    
    execute_on = 'initial timestep_begin'
  [../]
[]

[Constraints]
  [./disp_x]
    type = XFEMDispTimeConstraint
    variable = disp_x
    component=0
    E=208
    nu=0.3
    time_from=0.006
    time_to=0.01
    alpha = 1.0e3
    use_displaced_mesh = false
   # level_set_var = ls 
    geometric_cut_userobject = 'pf_marker_uo'
  [../]
  [./disp_y]
    type = XFEMDispTimeConstraint
    variable = disp_y
    component=1
    E=208
    nu=0.3
    time_from=0.006
    time_to=0.01
    alpha = 1.0e3
    #level_set_var = ls 
    use_displaced_mesh =false
    geometric_cut_userobject = 'pf_marker_uo'
  [../]
  [./disp_x_crack]
    type = XFEMDispTimeConstraint
    variable = disp_x
    component=0
    E=208
    nu=0.3
    time_from=0.006
    time_to=0.01
    alpha = 1.0e3
    use_displaced_mesh = false
   # level_set_var = ls 
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]
  [./disp_y_crack]
    type = XFEMDispTimeConstraint
    variable = disp_y
    component=1
    E=208
    nu=0.3
    time_from=0.006
    time_to=0.01
    alpha = 1.0e3
    #level_set_var = ls 
    use_displaced_mesh =false
    geometric_cut_userobject = 'line_seg_cut_uo'
  [../]

[]


[Materials]
  [./pfbulkmat]
    type = GenericConstantMaterial
    prop_names = 'gc_prop l visco'
    prop_values = '1e-3 0.02 1e-3'
  [../]
  [./define_mobility]
    type = ParsedMaterial
    material_property_names = 'gc_prop visco'
    f_name = L
    function = '1.0/(gc_prop * visco)'
  [../]
  [./define_kappa]
    type = ParsedMaterial
    material_property_names = 'gc_prop l'
    f_name = kappa_op
    function = 'gc_prop * l'
  [../]
  [./elasticity_tensor]
    type = ComputeElasticityTensor
    C_ijkl = '120.0 80.0'
    fill_method = symmetric_isotropic
  [../]
  [./elastic]
    type = ComputeIsotropicLinearElasticPFFractureStress
    c = c
    kdamage = 0
    F_name = E_el
  [../]
[]

[Postprocessors]
  [./resid_x]
    type = NodalSum
    variable = resid_x
    boundary = 2
  [../]
  [./resid_y]
    type = NodalSum
    variable = resid_y
    boundary = 2
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

  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package -ksp_gmres_restart -sub_ksp_type -sub_pc_type'
  petsc_options_value = 'lu       mumps                         101                preonly        lu'
  
  #petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  #petsc_options_value = 'asm      31                  preonly       lu           0'
  
  #petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart -sub_ksp_type -sub_pc_type'
  #petsc_options_value = 'hypre    boomeramg      201                  preonly       lu        '
  nl_rel_tol = 1e-8
  l_max_its = 10

  dt = 1e-4
  num_steps = 80
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus=true
[]

