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

from distutils.sysconfig import get_python_inc
import platform
import os
import subprocess
import ycm_core

DIR_OF_THIS_SCRIPT = os.path.abspath( os.path.dirname( __file__ ) )
DIR_OF_THIRD_PARTY = '../../../../Godot/godot-cpp'#os.path.join( DIR_OF_THIS_SCRIPT, 'third_party' )
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

# These are the compilation flags that will be used in case there's no
# compilation database set (by default, one is not set).
# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.
flags = [
'-Wall',
'-Wextra',
'-Werror',
'-Wno-long-long',
'-Wno-variadic-macros',
'-fexceptions',
'-DNDEBUG',
# THIS IS IMPORTANT! Without the '-x' flag, Clang won't know which language to
# use when compiling headers. So it will guess. Badly. So C++ headers will be
# compiled as C headers. You don't want that so ALWAYS specify the '-x' flag.
# For a C project, you would set this to 'c' instead of 'c++'.
'-x',
'c++',
'-I../../../../Godot/godot-cpp/' ,
'-I../../../../Godot/godot-cpp/cmake' ,
'-I../../../../Godot/godot-cpp/misc' ,
'-I../../../../Godot/godot-cpp/misc/hooks' ,
'-I../../../../Godot/godot-cpp/misc/scripts' ,
'-I../../../../Godot/godot-cpp/misc/ci' ,
'-I../../../../Godot/godot-cpp/__pycache__' ,
'-I../../../../Godot/godot-cpp/src' ,
'-I../../../../Godot/godot-cpp/src/variant' ,
'-I../../../../Godot/godot-cpp/src/core' ,
'-I../../../../Godot/godot-cpp/src/classes' ,
'-I../../../../Godot/godot-cpp/include' ,
'-I../../../../Godot/godot-cpp/include/godot_cpp' ,
'-I../../../../Godot/godot-cpp/include/godot_cpp/templates' ,
'-I../../../../Godot/godot-cpp/include/godot_cpp/variant' ,
'-I../../../../Godot/godot-cpp/include/godot_cpp/core' ,
'-I../../../../Godot/godot-cpp/include/godot_cpp/classes' ,
'-I../../../../Godot/godot-cpp/gdextension' ,
'-I../../../../Godot/godot-cpp/.github' ,
'-I../../../../Godot/godot-cpp/.github/actions' ,
'-I../../../../Godot/godot-cpp/.github/actions/godot-cache' ,
'-I../../../../Godot/godot-cpp/.github/workflows' ,
'-I../../../../Godot/godot-cpp/.github/ISSUE_TEMPLATE' ,
'-I../../../../Godot/godot-cpp/tools' ,
'-I../../../../Godot/godot-cpp/tools/__pycache__' ,
'-I../../../../Godot/godot-cpp/test' ,
'-I../../../../Godot/godot-cpp/test/project' ,
'-I../../../../Godot/godot-cpp/test/project/bin' ,
'-I../../../../Godot/godot-cpp/test/project/bin/libgdexample.macos.template_debug.framework' ,
'-I../../../../Godot/godot-cpp/test/project/bin/libgdexample.macos.template_debug.framework/Resources' ,
'-I../../../../Godot/godot-cpp/test/project/bin/libgdexample.macos.template_release.framework' ,
'-I../../../../Godot/godot-cpp/test/project/bin/libgdexample.macos.template_release.framework/Resources' ,
'-I../../../../Godot/godot-cpp/test/src' ,
'-I../../../../Godot/godot-cpp/gen' ,
'-I../../../../Godot/godot-cpp/gen/src' ,
'-I../../../../Godot/godot-cpp/gen/src/variant' ,
'-I../../../../Godot/godot-cpp/gen/src/classes' ,
'-I../../../../Godot/godot-cpp/gen/include' ,
'-I../../../../Godot/godot-cpp/gen/include/godot_cpp' ,
'-I../../../../Godot/godot-cpp/gen/include/godot_cpp/variant' ,
'-I../../../../Godot/godot-cpp/gen/include/godot_cpp/core' ,
'-I../../../../Godot/godot-cpp/gen/include/godot_cpp/classes' ,
'-I../../../../Godot/godot-cpp/bin' ,
'-std=c++17'
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
#compilation_database_folder = ''
#
#if os.path.exists( compilation_database_folder ):
#  database = ycm_core.CompilationDatabase( compilation_database_folder )
#else:
#  database = None
#
#
#def IsHeaderFile( filename ):
#  extension = os.path.splitext( filename )[ 1 ]
#  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]
#
#
#def FindCorrespondingSourceFile( filename ):
#  if IsHeaderFile( filename ):
#    basename = os.path.splitext( filename )[ 0 ]
#    for extension in SOURCE_EXTENSIONS:
#      replacement_file = basename + extension
#      if os.path.exists( replacement_file ):
#        return replacement_file
#  return filename
#
#
#def Settings( **kwargs ):
#  if kwargs[ 'language' ] == 'cfamily':
#    # If the file is a header, try to find the corresponding source file and
#    # retrieve its flags from the compilation database if using one. This is
#    # necessary since compilation databases don't have entries for header files.
#    # In addition, use this source file as the translation unit. This makes it
#    # possible to jump from a declaration in the header file to its definition
#    # in the corresponding source file.
#    filename = FindCorrespondingSourceFile( kwargs[ 'filename' ] )
#
#    if not database:
#      return {
#        'flags': flags,
#        'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT,
#        'override_filename': filename
#      }
#
#    compilation_info = database.GetCompilationInfoForFile( filename )
#    if not compilation_info.compiler_flags_:
#      return {}
#
#    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
#    # python list, but a "list-like" StringVec object.
#    final_flags = list( compilation_info.compiler_flags_ )
#
#    except ValueError:
#      pass
#
#    return {
#      'flags': final_flags,
#      'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
#      'override_filename': filename
#    }
#  return {}
#
#
#def GetStandardLibraryIndexInSysPath( sys_path ):
#  for path in sys_path:
#    if os.path.isfile( os.path.join( path, 'os.py' ) ):
#      return sys_path.index( path )
#  raise RuntimeError( 'Could not find standard library path in Python path.' )
#
#
#def PythonSysPath( **kwargs ):
#  sys_path = kwargs[ 'sys_path' ]
#  for folder in os.listdir( DIR_OF_THIRD_PARTY ):
#    if folder == 'python-future':
#      folder = os.path.join( folder, 'src' )
#      sys_path.insert( GetStandardLibraryIndexInSysPath( sys_path ) + 1,
#                       os.path.realpath( os.path.join( DIR_OF_THIRD_PARTY,
#                                                       folder ) ) )
#      continue
#
#    if folder == 'cregex':
#      interpreter_path = kwargs[ 'interpreter_path' ]
#      major_version = subprocess.check_output( [
#        interpreter_path, '-c', 'import sys; print( sys.version_info[ 0 ] )' ]
#      ).rstrip().decode( 'utf8' )
#      folder = os.path.join( folder, 'regex_{}'.format( major_version ) )
#
#    sys_path.insert( 0, os.path.realpath( os.path.join( DIR_OF_THIRD_PARTY,
#                                                        folder ) ) )
#  return sys_path
#
#gives me that sweet sweet tab complete
def Settings( **kwargs ):
  return {
          'flags': flags
  }
