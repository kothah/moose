[MeshGenerators]
  [img]
    type = ImageMeshGenerator
    dim = 2
    file = spiral_16x16.png
    scale_to_one = false
  []
[]

[Mesh]
  type = MeshGeneratorMesh
[]

[Outputs]
  exodus = true
[]
