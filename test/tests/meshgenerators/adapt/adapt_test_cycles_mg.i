[MeshGenerators]
  [./fmg]
    type = FileMeshGenerator
    file = square.e
    uniform_refine = 3
  []
[]

[Mesh]
  type = MeshGeneratorMesh
[]

[Variables]
  active = 'u v'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./v]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'udiff uconv uie vdiff'

  [./udiff]
    type = Diffusion
    variable = u
  [../]

  [./uconv]
    type = Convection
    variable = u
    velocity = '20 1 0'
  [../]

  [./uie]
    type = TimeDerivative
    variable = u
  [../]

  [./vdiff]
    type = Diffusion
    variable = v
  [../]
[]

[BCs]
  active = 'uleft uright vleft vright'

  [./uleft]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 0
  [../]

  [./uright]
    type = DirichletBC
    variable = u
    boundary = 2
    value = 1
  [../]

  [./vleft]
    type = DirichletBC
    variable = v
    boundary = 1
    value = 1
  [../]

  [./vright]
    type = DirichletBC
    variable = v
    boundary = 2
    value = 0
  [../]
[]

[Executioner]
  type = Transient

  solve_type = 'PJFNK'

  start_time = 0.0
  num_steps = 2
  dt = .1

  [./Adaptivity]
    refine_fraction = 0.3
    max_h_level = 7
    cycles_per_step = 2
  [../]
[]

[Outputs]
  file_base = out_cycles
  exodus = true
[]
