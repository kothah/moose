[Mesh]
  # ImageMesh ignores nx, xmin, xmax (and similarly for y and z) and
  # tries to read them from the image file...
  type = ImageMesh
  dim = 2

  # Be sure to choose a corresponding image name below!
  # file = image001_cropped3_closing_298.png         # full size, 157 Mb Exodus file!
  # file = eighth_image001_cropped3_closing_298.png  # 1/8
  file = sixteenth_image001_cropped3_closing_298.png # 1/16

  # Uncomment to maintain 1:1 ratio between number of pixels and mesh size.
  # scale_to_one = false

  # Uncomment to set cells_per_pixel to something other than the default value of 1.0.
  # Must be <= 1.
  # cells_per_pixel = .75

  # To crop an image to e.g. 1/8th size, install ImageMagick and run:
  #  convert image001_cropped3_closing_298.png -crop 230x198+100+100 eighth_image001_cropped3_closing_298.png
  # Note: Do not use 'sips' on OSX to crop!  It actually interpolates
  # the colors in the image instead of just cropping.
[]

[Variables]
  [./u]
    # The NodalFloodCount object requires an *nodal* variable in order
    # to work (otherwise it segfaults).
  [../]
[]

[AuxVariables]
  [./grain_auxvar]
    #order = CONSTANT
    #family = MONOMIAL
  [../]
  [./pid]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./nodal_flood_aux]
    # We definitely need to execute this AuxKernel on TIMESTEP,
    # otherwise the grain_auxvar won't be shown in paraview...
    execute_on = 'TIMESTEP'
    # This auxkernel is initialized *before* the variable u is set
    # from FunctionIC, so it will always be zero initially...
    variable = grain_auxvar
    type = NodalFloodCountAux
    bubble_object = flood_count_pp
  [../]
  [./pid]
    type = ProcessorIDAux
    variable = pid
    execute_on = 'initial timestep'
  [../]
[]


[Functions]
  [./tif]
    type = ImageFunction
    # Filename - match with mesh size above!
    # file_base = image001_cropped3_closing         # full
    # file_base = eighth_image001_cropped3_closing  # 1/8
    file_base = sixteenth_image001_cropped3_closing # 1/16

    # The file extension of our images
    file_type = png

    # file range is parsed as a vector of unsigned.  If it only has 1
    # entry, only a single file is read.
    file_range = '298'
  [../]
[]

[ICs]
  [./u_ic]
    type = FunctionIC
    function = tif
    variable = u
  [../]
[]

[Postprocessors]
  [./flood_count_pp]
    execute_on = 'TIMESTEP'
    type = NodalFloodCount
    variable = u
    # For some reason I don't understand yet, the ImageFunction thing
    # returns either 0 or 62735 for the images we have... so a value
    # of 1.0 is definitely between those two values :-P
    threshold = 1.0

    # We define the "bubbles/grains" to be regions where u is greater-than the threshold.
    use_less_than_threshold_comparison = false

    # File to write bubble volume data to
    bubble_volume_file = bubble_volumes.csv

    # Explicitly turn on the boundary-intersecting volume calculation
    compute_boundary_intersecting_volume = true
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[../]

[Executioner]
  type = Steady
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = false
    linear_residuals = false
  [../]
[]
