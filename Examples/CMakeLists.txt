cmake_minimum_required (VERSION 3.8)

project(dto)

add_subdirectory(ExternalLibraries)

# Header `DependencyTypeOverride.h` lives in the repository root.
# Examples include it as: `#include <DependencyTypeOverride.h>`
set(dtoInclude "${CMAKE_CURRENT_LIST_DIR}/..")

add_subdirectory(1_SympleTypeOverriding)
add_subdirectory(2_InDemandDefault)
