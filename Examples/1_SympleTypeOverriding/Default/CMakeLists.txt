#

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SourceDir "src")

set(SourceFiles "${SourceDir}/1_SimpleTypeDefault.cpp" "${SourceDir}/Dependant.cpp" "${SourceDir}/Dependant.h" "${SourceDir}/Dependencies.cpp" "${SourceDir}/Dependencies.h")

include_directories(${SourceDir}/dto ${dtoInclude})

add_executable (1_Default ${SourceFiles})
