CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes      	   num_elem      
num_el_blk        num_node_sets         num_el_in_blk1        num_nod_per_el1       num_el_in_blk2        num_nod_per_el2       num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_var       num_info   �         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         &nodal_constraint_displaced_test_out.e      maximum_name_length                    
time_whole                            Z   	eb_status                             L   eb_prop1               name      ID              T   	ns_status         	                    \   ns_prop1      	         name      ID              l   coordx                      H      |   coordy                      H      �   coordz                      H         eb_names                       D      T   ns_names      	                 �      �   
coor_names                         d      	   node_num_map                    $      	�   connect1      
            	elem_type         EDGE2               	�   connect2                  	elem_type         EDGE2                	�   elem_num_map                          	�   node_ns1                          	�   node_ns2                          	�   node_ns3                          
    node_ns4                          
   vals_nod_var1                          H      Z   vals_nod_var2                          H      ZX   name_nod_var                       D      
   info_records                      O�      
L                                    ?�      ?�UUUUUV?�UUUUUV        ?�(�\)?�(�\(?�(�\(?�(�\'@ z�G�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       	                                          	                        	         disp_x                           u                                  ####################                                                             # Created by MOOSE #                                                             ####################                                                             ### Command Line Arguments ###                                                    -i nodal_constraint_displaced_test.i### Version Info ###                        Framework Information:                                                           MOOSE Version:           git commit b20e3de46f on 2018-06-13                     LibMesh Version:         ceb1e02bee97b3758bfcdc37cb87bc8954a89030                PETSc Version:           3.8.3                                                   Current Time:            Mon Jun 18 10:02:42 2018                                Executable Timestamp:    Mon Jun 18 10:02:16 2018                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 inactive                       =                                                 element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [AuxKernels]                                                                                                                                                        [./disp_x_ak]                                                                      inactive                     =                                                   isObjectAction               = 1                                                 type                         = ConstantAux                                       block                        = INVALID                                           boundary                     = INVALID                                           control_tags                 = AuxKernels                                        enable                       = 1                                                 execute_on                   = LINEAR                                            seed                         = 0                                                 use_displaced_mesh           = 0                                                 value                        = 1                                                 variable                     = disp_x                                          [../]                                                                          []                                                                                                                                                                [AuxVariables]                                                                                                                                                      [./disp_x]                                                                         block                        = INVALID                                           family                       = LAGRANGE                                          inactive                     =                                                   initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                [BCs]                                                                                                                                                               [./left]                                                                           boundary                     = 1                                                 control_tags                 = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 matrix_tags                  = system                                            type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                           diag_save_in                 = INVALID                                           save_in                      = INVALID                                           seed                         = 0                                                 value                        = 1                                               [../]                                                                                                                                                             [./right]                                                                          boundary                     = 4                                                 control_tags                 = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 matrix_tags                  = system                                            type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                           diag_save_in                 = INVALID                                           save_in                      = INVALID                                           seed                         = 0                                                 value                        = 3                                               [../]                                                                          []                                                                                                                                                                [Constraints]                                                                                                                                                       [./c1]                                                                             inactive                     =                                                   isObjectAction               = 1                                                 type                         = EqualValueNodalConstraint                         control_tags                 = Constraints                                       enable                       = 1                                                 execute_on                   = LINEAR                                            formulation                  = penalty                                           master                       = 0                                                 penalty                      = 100000                                            slave                        = 4                                                 use_displaced_mesh           = 1                                                 variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      inactive                       =                                                 isObjectAction                 = 1                                               type                           = Steady                                          compute_initial_residual_before_preset_bcs = 0                                   contact_line_search_allowed_lambda_cuts = 2                                      contact_line_search_ltol       = INVALID                                         control_tags                   =                                                 enable                         = 1                                               l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = default                                         line_search_package            = petsc                                           mffd_type                      = wp                                              nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         restart_file_base              =                                                 solve_type                     = PJFNK                                           splitting                      = INVALID                                       []                                                                                                                                                                [Executioner]                                                                    []                                                                                                                                                                [Kernels]                                                                                                                                                           [./diff]                                                                           inactive                     =                                                   isObjectAction               = 1                                                 type                         = Diffusion                                         block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 extra_matrix_tags            = INVALID                                           extra_vector_tags            = INVALID                                           implicit                     = 1                                                 matrix_tags                  = system                                            save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                                 vector_tags                  = nontime                                         [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             inactive                       =                                                 displacements                  = disp_x                                          block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         isObjectAction                 = 1                                               second_order                   = 0                                               skip_partitioning              = 0                                               type                           = FileMesh                                        uniform_refine                 = 0                                               allow_renumbering              = 1                                               centroid_partitioner_direction = INVALID                                         construct_node_list_from_side_list = 1                                           control_tags                   =                                                 dim                            = 1                                               enable                         = 1                                               file                           = /Users/andrsd/workspace/moose/test/tests/c... onstraints/nodal_constraint/2-lines.e                                              ghosting_patch_size            = INVALID                                         max_leaf_size                  = 10                                              nemesis                        = 0                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_size                     = 40                                              patch_update_strategy          = never                                         []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         inactive                       =                                                 interval                       = 1                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                             []                                                                                                                                                                [Variables]                                                                                                                                                         [./u]                                                                              block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          inactive                     =                                                   initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                                                                                       ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�������?�      ?�������?�������@������@������@������@������@������