# Generated by YCM Generator at 2017-12-11 11:48:41.892948

# This file is NOT licensed under the GPLv3, which is the license for the rest
# of YouCompleteMe.
#
# Here's the license text for this file:
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

import os
import ycm_core

flags = [
    '-x',
    'c++',
    '-DHAVE_CONFIG_H',
    '-DMETHOD=opt',
    '-DNDEBUG',
    '-DPIC',
    '-I/Users/-DNDEBUG',
    '-I/Users/k/contrib/gtest',
    '-I/Users/kothari/MOOSE_ICS/moose/framewo-DNDEBUG',
    '-I/Users/kothari/MOOSE_ICS/moose/framewok/contrib/gtest',
    '-I/Users/kothari/MOOSE_ICS/moose/framewokothari/MOOSE_ICS/moose/framework/include/ics',
    '-I/Users/kothari/MOOSE_ICS/moose/framewor-DNDEBUG',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/boost/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/exodiff',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/gtest',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/hit',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/jsoncpp/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/jsoncpp/include/json',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/mtwist/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/pcre/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/contrib/tinydir/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/actions',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/auxkernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/base',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/bcs',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/constraints',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/controls',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/dampers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/dgkernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/dirackernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/distributions',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/executioners',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/functions',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/geomsearch',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/ics',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/indicators',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/interfacekernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/kernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/markers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/materials',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/mesh',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/meshmodifiers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/multiapps',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/nodalkernels',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/outputs',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/outputs/formatters',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/parser',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/partitioner',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/postprocessors',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/preconditioners',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/predictors',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/restart',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/samplers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/splits',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/timeintegrators',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/timesteppers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/transfers',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/userobject',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/utils',
    '-I/Users/kothari/MOOSE_ICS/moose/framework/include/vectorpostprocessors',
    '-I/Users/kothari/MOOSE_ICS/moose/frameworkothari/MOOSE_ICS/moose/framework/include/ics',
    '-I/Users/kothari/MOOSE_ICS/moose/frameworrk/include/predictors',
    '-I/Users/kothari/MOOSE_ICS/moose/scripts/../libmesh/installed/include',
    '-I/Users/rk/include/predictors',
    '-I/opt/X11/include',
    '-I/opt/moose/miniconda/include/python2.7',
    '-I/opt/moose/mpich/mpich-3.2/clang-opt/include',
    '-I/opt/moose/petsc/mpich_petsc-3.7.5/clang-opt-superlu//include',
    '-I/opt/moose/petsc/mpich_petsc-3.7.5/clang-opt-superlu/include',
    '-I/opt/moose/tbb/include',
    '-Werror=reorder',
    '-Werror=return-type',
    '-Woverlength-strings',
    '-Wunused',
    '-Wunused-parameter',
    '-install_name',
    '-std=c++11',
    '-std=gnu++11',
]


# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.C', '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.H', '.h', '.hxx', '.hpp', '.hh' ]


def GetCompilationInfoForFile( filename ):
  # The compilation_commands.json file generated by CMake does not have entries
  # for header files. So we do our best by asking the db for flags for a
  # corresponding source file, if any. If one exists, the flags for that file
  # should be good enough.
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )


def FlagsForFile( filename, **kwargs ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = GetCompilationInfoForFile( filename )
    if not compilation_info:
      return None

    final_flags = MakeRelativePathsInFlagsAbsolute(
      compilation_info.compiler_flags_,
      compilation_info.compiler_working_dir_ )

  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }

