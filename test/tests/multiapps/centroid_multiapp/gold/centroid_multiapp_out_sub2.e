CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem   	   
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1     	   num_nod_per_el1       num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_var       num_glo_var       num_info  �         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         centroid_multiapp_out_sub2.e       maximum_name_length                 "   
time_whole                            �x   	eb_status                             	|   eb_prop1               name      ID              	�   	ns_status         	                    	�   ns_prop1      	         name      ID              	�   	ss_status         
                    	�   ss_prop1      
         name      ID              	�   coordx                      �      	�   coordy                      �      
D   eb_names                       $      
�   ns_names      	                 �      
�   ss_names      
                 �      l   
coor_names                         D      �   node_num_map                    @      4   connect1                  	elem_type         QUAD4         �      t   elem_num_map                    $         elem_ss1                          (   side_ss1                          4   elem_ss2                          @   side_ss2                          L   elem_ss3                          X   side_ss3                          d   elem_ss4                          p   side_ss4                          |   node_ns1                          �   node_ns2                          �   node_ns3                          �   node_ns4                          �   vals_nod_var1                          �      ��   vals_nod_var2                          �      �    name_nod_var                       D      �   name_glo_var                       D         vals_glo_var                             ��   info_records                      �(      P                                                         ?�UUUUUU?ə�����?ə�����?�UUUUUU?�������?�������?�?�?ə�����?�UUUUUU?�������?�?ə�����?�UUUUUU?�������?�?ꪪ����?ꪪ����?뻻����?뻻����?ꪪ����?뻻����?ꪪ����?뻻����?�������?�������?�������?�������?�������?�������?�������?�������                                    bottom                           left                             top                              right                            bottom                           left                             top                              right                                                                                                                           	   
                                                               	   
            	               
   	         	                                                	                                             	            	                                 
                              x                                y                                  incoming_x                       incoming_y                         ####################                                                             # Created by MOOSE #                                                             ####################                                                             ### Command Line Arguments ###                                                    -i centroid_multiapp.i### Input File ###                                                                                                                         []                                                                                 inactive                       =                                                 initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [BCs]                                                                                                                                                               [./left_x]                                                                         _boundary_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:50                                               _boundary_fullpath           = BCs/left_x/boundary                               _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:48                                               _type_fullpath               = BCs/left_x/type                                   _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:49                                               _variable_fullpath           = BCs/left_x/variable                               boundary                     = left                                              control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = x                                                 _value_fileloc               = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:51                                               _value_fullpath              = BCs/left_x/value                                  diag_save_in                 = INVALID                                           save_in                      = INVALID                                           seed                         = 0                                                 value                        = 0                                               [../]                                                                                                                                                             [./left_y]                                                                         _boundary_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:38                                               _boundary_fullpath           = BCs/left_y/boundary                               _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:36                                               _type_fullpath               = BCs/left_y/type                                   _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:37                                               _variable_fullpath           = BCs/left_y/variable                               boundary                     = left                                              control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = y                                                 _value_fileloc               = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:39                                               _value_fullpath              = BCs/left_y/value                                  diag_save_in                 = INVALID                                           save_in                      = INVALID                                           seed                         = 0                                                 value                        = 0                                               [../]                                                                                                                                                             [./right_x]                                                                        _boundary_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:32                                               _boundary_fullpath           = BCs/right_x/boundary                              _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:30                                               _type_fullpath               = BCs/right_x/type                                  _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:31                                               _variable_fullpath           = BCs/right_x/variable                              boundary                     = right                                             control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 type                         = PostprocessorDirichletBC                          use_displaced_mesh           = 0                                                 variable                     = x                                                 _postprocessor_fileloc       = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:33                                               _postprocessor_fullpath      = BCs/right_x/postprocessor                         diag_save_in                 = INVALID                                           postprocessor                = incoming_x                                        save_in                      = INVALID                                           seed                         = 0                                               [../]                                                                                                                                                             [./right_y]                                                                        _boundary_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:44                                               _boundary_fullpath           = BCs/right_y/boundary                              _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:42                                               _type_fullpath               = BCs/right_y/type                                  _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:43                                               _variable_fullpath           = BCs/right_y/variable                              boundary                     = right                                             control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 inactive                     =                                                   isObjectAction               = 1                                                 type                         = PostprocessorDirichletBC                          use_displaced_mesh           = 0                                                 variable                     = y                                                 _postprocessor_fileloc       = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:45                                               _postprocessor_fullpath      = BCs/right_y/postprocessor                         diag_save_in                 = INVALID                                           postprocessor                = incoming_y                                        save_in                      = INVALID                                           seed                         = 0                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      _type_fileloc                  = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:56                                             _type_fullpath                 = Executioner/type                                inactive                       =                                                 isObjectAction                 = 1                                               type                           = Transient                                       _num_steps_fileloc             = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:57                                             _num_steps_fullpath            = Executioner/num_steps                           _petsc_options_iname_fileloc   = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:58                                             _petsc_options_iname_fullpath  = Executioner/petsc_options_iname                 _petsc_options_value_fileloc   = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:59                                             _petsc_options_value_fullpath  = Executioner/petsc_options_value                 _solve_type_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:60                                             _solve_type_fullpath           = Executioner/solve_type                          abort_on_solve_fail            = 0                                               compute_initial_residual_before_preset_bcs = 0                                   control_tags                   =                                                 dt                             = 1                                               dtmax                          = 1e+30                                           dtmin                          = 2e-14                                           enable                         = 1                                               end_time                       = 1e+30                                           l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = default                                         max_xfem_update                = 4294967295                                      mffd_type                      = wp                                              n_startup_steps                = 0                                               nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               num_steps                      = 1                                               petsc_options                  = INVALID                                         petsc_options_iname            = '-pc_type -pc_hypre_type'                       petsc_options_value            = 'hypre boomeramg'                               picard_abs_tol                 = 1e-50                                           picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           relaxation_factor              = 1                                               relaxed_variables              =                                                 reset_dt                       = 0                                               restart_file_base              =                                                 scheme                         = implicit-euler                                  solve_type                     = PJFNK                                           splitting                      = INVALID                                         ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               time_period_ends               = INVALID                                         time_period_starts             = INVALID                                         time_periods                   = INVALID                                         timestep_tolerance             = 2e-14                                           trans_ss_check                 = 0                                               use_multiapp_dt                = 0                                               verbose                        = 0                                             []                                                                                                                                                                [Executioner]                                                                      _fe_problem                    = 0x7fc85a003018                                  _fe_problem_base               = 0x7fc85a003018                                []                                                                                                                                                                [Kernels]                                                                                                                                                           [./diff_x]                                                                         _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:23                                               _type_fullpath               = Kernels/diff_x/type                               inactive                     =                                                   isObjectAction               = 1                                                 type                         = Diffusion                                         _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:24                                               _variable_fullpath           = Kernels/diff_x/variable                           block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           eigen_kernel                 = 0                                                 enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = x                                               [../]                                                                                                                                                             [./diff_y]                                                                         _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:19                                               _type_fullpath               = Kernels/diff_y/type                               inactive                     =                                                   isObjectAction               = 1                                                 type                         = Diffusion                                         _variable_fileloc            = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:20                                               _variable_fullpath           = Kernels/diff_y/variable                           block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           eigen_kernel                 = 0                                                 enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = y                                               [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             inactive                       =                                                 displacements                  = INVALID                                         _type_fileloc                  = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:2                                              _type_fullpath                 = Mesh/type                                       block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         isObjectAction                 = 1                                               second_order                   = 0                                               skip_partitioning              = 0                                               type                           = GeneratedMesh                                   uniform_refine                 = 0                                               _dim_fileloc                   = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:3                                              _dim_fullpath                  = Mesh/dim                                        _nx_fileloc                    = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:4                                              _nx_fullpath                   = Mesh/nx                                         _ny_fileloc                    = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:5                                              _ny_fullpath                   = Mesh/ny                                         _xmax_fileloc                  = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:7                                              _xmax_fullpath                 = Mesh/xmax                                       _ymax_fileloc                  = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:6                                              _ymax_fullpath                 = Mesh/ymax                                       allow_renumbering              = 1                                               bias_x                         = 1                                               bias_y                         = 1                                               bias_z                         = 1                                               centroid_partitioner_direction = INVALID                                         construct_node_list_from_side_list = 1                                           control_tags                   =                                                 dim                            = 2                                               elem_type                      = INVALID                                         enable                         = 1                                               gauss_lobatto_grid             = 0                                               ghost_point_neighbors          = 0                                               ghosting_patch_size            = INVALID                                         max_leaf_size                  = 10                                              nemesis                        = 0                                               num_ghosted_layers             = 1                                               nx                             = 3                                               ny                             = 3                                               nz                             = 1                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_size                     = 40                                              patch_update_strategy          = never                                           xmax                           = 0.1                                             xmin                           = 0                                               ymax                           = 0.1                                             ymin                           = 0                                               zmax                           = 1                                               zmin                           = 0                                             []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          _exodus_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:64                                             _exodus_fullpath               = Outputs/exodus                                  append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         inactive                       =                                                 interval                       = 1                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                             []                                                                                                                                                                [Postprocessors]                                                                                                                                                    [./incoming_x]                                                                     _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:69                                               _type_fullpath               = Postprocessors/incoming_x/type                    inactive                     =                                                   isObjectAction               = 1                                                 type                         = Receiver                                          _execute_on_fileloc          = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:70                                               _execute_on_fullpath         = Postprocessors/incoming_x/execute_on              allow_duplicate_execution_on_initial = 0                                         control_tags                 = Postprocessors                                    default                      = INVALID                                           enable                       = 1                                                 execute_on                   = TIMESTEP_BEGIN                                    force_preaux                 = 0                                                 initialize_old               = 1                                                 outputs                      = INVALID                                           use_displaced_mesh           = 0                                               [../]                                                                                                                                                             [./incoming_y]                                                                     _type_fileloc                = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:73                                               _type_fullpath               = Postprocessors/incoming_y/type                    inactive                     =                                                   isObjectAction               = 1                                                 type                         = Receiver                                          _execute_on_fileloc          = /Users/gastdr/projects/moose/test/tests/mu... ltiapps/centroid_multiapp/sub_app.i:74                                               _execute_on_fullpath         = Postprocessors/incoming_y/execute_on              allow_duplicate_execution_on_initial = 0                                         control_tags                 = Postprocessors                                    default                      = INVALID                                           enable                       = 1                                                 execute_on                   = TIMESTEP_BEGIN                                    force_preaux                 = 0                                                 initialize_old               = 1                                                 outputs                      = INVALID                                           use_displaced_mesh           = 0                                               [../]                                                                          []                                                                                                                                                                [Variables]                                                                                                                                                         [./x]                                                                              block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          inactive                     =                                                   initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./y]                                                                              block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          inactive                     =                                                   initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                                                                                                                                                                                                                       ?�              ?�q�q�?�q�q�        ?�q�q�?�q�q�?�UUUUUT?�UUUUUT?�q�q�        ?�q�q�?�UUUUUT?�q�q�        ?�q�q�?�UUUUUT        ?��q�q?��q�p        ?��q�m?��q�o?ꪪ����?ꪪ����?��q�n        ?��q�r?ꪪ����?��q�p        ?��q�m?ꪪ����?�UUUUUT?ꪪ����