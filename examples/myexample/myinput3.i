[Mesh]
    file = mug.e
[]

[Variables]
    [./convected]
        order = FIRST
        family = LAGRANGE
    [../]
    [./diffused]
        order = FIRST
        family = LAGRANGE
    [../]
[]

[Kernels]
    [./diff_convected]
        type = Diffusion
        variable = convected
    [../]

    [./conv]
        type = HardikGradConvection
        variable = convected
        grad_variable = diffused
    [../]

    [./diff_difused]
        type = Diffusion
        variable = diffused
    [../]
[]

[BCs]
    [./bottom_convected]
        type = DirichletBC
        variable = convected
        boundary = 'bottom'
        value = 1
    [../]
    [./bottom_diffuesd]
        type = DirichletBC
        variable = diffused
        boundary = 'bottom'
        value = 2
    [../]

    [./top_convected]
        type = DirichletBC
        variable = convected
        boundary = 'top'
        value = 0
    [../]
    [./top_diffuesd]
        type = DirichletBC
        variable = diffused
        boundary = 'top'
        value = 0
    [../]

[]

[Executioner]
    type = Steady
    solve_type = 'PJFNK'
[]

[Outputs]
    execute_on = 'timestep_end'
    exodus = true
[]
