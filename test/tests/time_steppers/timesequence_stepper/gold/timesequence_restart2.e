CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1    	   num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_var       num_info  "         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         timesequence_restart2.e    maximum_name_length                    
time_whole                            i�   	eb_status                             �   eb_prop1               name      ID              �   	ns_status         	                    �   ns_prop1      	         name      ID              �   	ss_status         
                    �   ss_prop1      
         name      ID              �   coordx                      �      	   coordy                      �      	�   eb_names                       $      
�   ns_names      	                 �      
�   ss_names      
                 �      @   
coor_names                         D      �   node_num_map                    d         connect1                  	elem_type         QUAD9         �      l   elem_num_map                          �   elem_ss1                             side_ss1                             elem_ss2                             side_ss2                          $   elem_ss3                          ,   side_ss3                          4   elem_ss4                          <   side_ss4                          D   node_ns1                          L   node_ns2                          `   node_ns3                          t   node_ns4                          �   vals_nod_var1                          �      i�   name_nod_var                       $      �   info_records                      [�      �                                                         ��                      ��      ��              ��      ��      ��      ?�      ?�      ?�      ?�      ?�      ?�              ��              ��      ��      ��      ?�      ?�      ?�      ?�      ��      ��                      ��      ��              ��      ��      ��              ��      ��              ��      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                                          top                              left                             right                            bottom                           top                              right                            bottom                           left                                                                                                                            	   
                                                                        	      
                                                                                                                                                                                 
               
   u                                   ####################?�
=p��@ �fffff@ �ffffg?�
=p��?�
=p��?�
=p��@
=p��?�
=p# Created by MOOSE #�
=p��@
=p��@ �fffff@ �ffffg?�
=p��                      ####################                                                             ### Command Line Arguments ###                                                   -i                                                                               timesequence_restart2.i                                                          Outputs/file_base=timesequence_restart2                                          --error                                                                          --no-gdb-backtrace                                                                                                                                                ### Version Info ###                                                             Framework Information:                                                           MOOSE version:           git commit 3254346 on 2016-08-04                        PETSc Version:           3.6.4                                                   Current Time:            Thu Aug  4 12:27:21 2016                                Executable Timestamp:    Thu Aug  4 11:57:59 2016                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [BCs]                                                                                                                                                               [./all]                                                                            boundary                     = 'left right top bottom'                           control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 type                         = FunctionDirichletBC                               use_displaced_mesh           = 0                                                 variable                     = u                                                 diag_save_in                 = INVALID                                           function                     = exact_fn                                          save_in                      = INVALID                                           seed                         = 0                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      type                           = Transient                                       abort_on_solve_fail            = 0                                               compute_initial_residual_before_preset_bcs = 0                                   control_tags                   =                                                 dt                             = 1                                               dtmax                          = 1e+30                                           dtmin                          = 2e-14                                           enable                         = 1                                               end_time                       = 4                                               l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = default                                         max_xfem_update                = 4294967295                                      n_startup_steps                = 0                                               nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               num_steps                      = 4294967295                                      petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         picard_abs_tol                 = 1e-50                                           picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           reset_dt                       = 0                                               restart_file_base              =                                                 scheme                         = INVALID                                         solve_type                     = INVALID                                         splitting                      = INVALID                                         ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               time_period_ends               = INVALID                                         time_period_starts             = INVALID                                         time_periods                   = INVALID                                         timestep_tolerance             = 2e-14                                           trans_ss_check                 = 0                                               use_multiapp_dt                = 0                                               verbose                        = 0                                                                                                                                [./TimeStepper]                                                                    type                         = TimeSequenceStepper                               _executioner                 = 0x7fab8a65e6f0                                    _fe_problem                  = 0x7fab8c804e00                                    control_tags                 = Executioner                                       enable                       = 1                                                 reset_dt                     = 0                                                 time_sequence                = '0 0.85 1.3 2 4'                                [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      _fe_problem                    = 0x7fab8c804e00                                                                                                                   [./TimeStepper]                                                                  [../]                                                                          []                                                                                                                                                                [Functions]                                                                                                                                                         [./exact_fn]                                                                       type                         = ParsedFunction                                    control_tags                 = Functions                                         enable                       = 1                                                 vals                         = INVALID                                           value                        = t*t*(x*x+y*y)                                     vars                         = INVALID                                         [../]                                                                                                                                                             [./forcing_fn]                                                                     type                         = ParsedFunction                                    control_tags                 = Functions                                         enable                       = 1                                                 vals                         = INVALID                                           value                        = 2*t*(x*x+y*y)-4*t*t                               vars                         = INVALID                                         [../]                                                                          []                                                                                                                                                                [ICs]                                                                                                                                                               [./u_var]                                                                          type                         = FunctionIC                                        block                        = INVALID                                           boundary                     = INVALID                                           control_tags                 = ICs                                               enable                       = 1                                                 function                     = exact_fn                                          variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Kernels]                                                                                                                                                           [./diff]                                                                           type                         = Diffusion                                         block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                                                                                                             [./ffn]                                                                            type                         = UserForcingFunction                               block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 function                     = forcing_fn                                        implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                                                                                                             [./td]                                                                             type                         = TimeDerivative                                    block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 lumping                      = 0                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             displacements                  = INVALID                                         block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         patch_size                     = 40                                              second_order                   = 0                                               skip_partitioning              = 0                                               type                           = FileMesh                                        uniform_refine                 = 0                                               centroid_partitioner_direction = INVALID                                         construct_node_list_from_side_list = 1                                           control_tags                   =                                                 dim                            = 3                                               distribution                   = DEFAULT                                         enable                         = 1                                               file                           = timesequence_restart1_cp/0002_mesh.cpr          nemesis                        = 0                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_update_strategy          = never                                         []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = timesequence_restart2                           gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         interval                       = 1                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                             []                                                                                                                                                                [Problem]                                                                          block                          = INVALID                                         coord_type                     = XYZ                                             fe_cache                       = 0                                               kernel_coverage_check          = 1                                               material_coverage_check        = 1                                               name                           = 'MOOSE Problem'                                 restart_file_base              = timesequence_restart1_cp/0002                   rz_coord_axis                  = Y                                               type                           = FEProblem                                       use_legacy_uo_aux_computation  = INVALID                                         use_legacy_uo_initialization   = INVALID                                         library_path                   =                                                 object_names                   = INVALID                                         register_objects_from          = INVALID                                         control_tags                   =                                                 dimNearNullSpace               = 0                                               dimNullSpace                   = 0                                               enable                         = 1                                               error_on_jacobian_nonzero_reallocation = 0                                       force_restart                  = 0                                               petsc_inames                   =                                                 petsc_options                  = INVALID                                         petsc_values                   =                                                 solve                          = 1                                               use_nonlinear                  = 1                                             []                                                                                                                                                                [Variables]                                                                                                                                                         [./u]                                                                              block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = SECOND                                            outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                 ?�������@
=p��?�
=p��        ?�
=p��@ �ffffg?�
=p��?�
=p��@ �ffffg?�
=p��@
=p��?�
=p��@ �fffff@ �ffffg?�
=p��?�
=p��?�
=p��@
=p��?�
=p��@ �fffff@ �ffffg?�
=p��@
=p��@ �fffff@ �ffffg?�
=p��@       @      �@     �?�V��<u@     �@     �?�G]�?�Gb�@     �@ `q��G@      �@     �@     �@     �?�G[9@ `q��I�@     �@      �?�Ga�@     �@     �@ `q��GL@      �@     �@     �@ `q��IQ@      @@    �@0    �?�ڟ�\g@0    �@4    @��r�]�@��r�m�@4    @ O�	�/�@@    �@0    �@4     �@4    @��r�?�@ O�	�:J@0    �@@    �@��r�M<@4     �@4    @ O�	�/�@@    �@4     �@4    @ O�	�-�