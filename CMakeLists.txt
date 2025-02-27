cmake_minimum_required(VERSION 3.10)
project(CS380CLAB LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(LLVM CONFIG)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# We defer the version checking to this statement
if("${LLVM_VERSION_MAJOR}" VERSION_LESS 19)
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 19 or above")
endif()

# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# Build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE
      STRING "Build type (default Debug):" FORCE)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall\
  -fdiagnostics-color=always")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fvisibility-inlines-hidden" SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
if (${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()

add_library(loop-analysis-pass SHARED
  ./UTEID-loop-analysis-pass.cpp
)

add_library(loop-opt-pass SHARED
  ./UTEID-loop-opt-pass.cpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Add link flags specific to Darwin
  message("OSx Compile. add some silly flags to fix dylib")
  target_link_options(loop-analysis-pass PRIVATE -undefined dynamic_lookup)
  target_link_options(loop-opt-pass PRIVATE -undefined dynamic_lookup)
endif()
