
cmake_minimum_required (VERSION 3.8)

project(dto)

add_subdirectory(ExternalLibraries)

set(dtoInclude "../../ExternalLibraries/dto")

add_subdirectory(1_SympleTypeOverriding)
add_subdirectory(2_InDemandDefault)
