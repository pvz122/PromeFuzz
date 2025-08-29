cmake_minimum_required(VERSION 3.13.4)
project(PromeFuzz)

#===============================================================================
# 0. GET CLANG INSTALLATION DIR
#===============================================================================
# `CLANG_INSTALL_DIR` is the key CMake variable - it points
# to a Clang installation directory. For the sake of completeness,
# <PackageName>_DIR (i.e. `Clang_DIR`) and <PackageName>_ROOT (i.e.
# `Clang_ROOT`) are also supported. Visit CMake documentation for more details:
#   https://cmake.org/cmake/help/latest/command/find_package.html
# Use only _one_ of these variables.

# execute "llvm-config --prefix" to get the installation directory
execute_process(COMMAND llvm-config --prefix
  OUTPUT_VARIABLE CLANG_INSTALL_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

#===============================================================================
# 1. VERIFY CLANG INSTALLATION DIR
#===============================================================================
set(CT_LLVM_INCLUDE_DIR "${CLANG_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${CT_LLVM_INCLUDE_DIR}")
message(FATAL_ERROR
  " CLANG_INSTALL_DIR (${CT_LLVM_INCLUDE_DIR}) is invalid.")
endif()

set(CT_LLVM_CMAKE_FILE
  "${CLANG_INSTALL_DIR}/lib/cmake/clang/ClangConfig.cmake")
if(NOT EXISTS "${CT_LLVM_CMAKE_FILE}")
message(FATAL_ERROR
  " CT_LLVM_CMAKE_FILE (${CT_LLVM_CMAKE_FILE}) is invalid.")
endif()

#===============================================================================
# 2. LOAD CLANG CONFIGURATION
#    Extracted from:
#    http://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
#===============================================================================
list(APPEND CMAKE_PREFIX_PATH "${CLANG_INSTALL_DIR}/lib/cmake/clang/")

find_package(Clang REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)


# Sanity check. As Clang does not expose e.g. `CLANG_VERSION_MAJOR` through
# AddClang.cmake, we have to use LLVM_VERSION_MAJOR instead.
if("12" VERSION_GREATER "${LLVM_VERSION_MAJOR}")
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 12+")
endif()

message(STATUS "Found Clang ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_INSTALL_DIR}")

message("CLANG STATUS:
  Includes (clang)    ${CLANG_INCLUDE_DIRS}
  Includes (llvm)     ${LLVM_INCLUDE_DIRS}"
)

# Set the LLVM and Clang header and library paths
include_directories(SYSTEM "${LLVM_INCLUDE_DIRS};${CLANG_INCLUDE_DIRS}")

#===============================================================================
# 3. AFGen BUILD CONFIGURATION
#===============================================================================
# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE
      STRING "Build type (default Debug):" FORCE)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall\
    -fdiagnostics-color=always")

# LLVM/Clang is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# -fvisibility-inlines-hidden is set when building LLVM and on Darwin warnings
# are triggered if AFGen is built without this flag (though otherwise it
# builds fine). For consistency, add it here too.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fvisibility-inlines-hidden"
  SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
if(${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()

# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#===============================================================================
# 4. ADD SUB-TARGETS
# Doing this at the end so that all definitions and link/include paths are
# available for the sub-projects.
#===============================================================================
add_subdirectory(processor/cxx)
