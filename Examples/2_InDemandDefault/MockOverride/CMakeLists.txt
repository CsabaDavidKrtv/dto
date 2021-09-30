

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(GoogleTest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(DefaultSourceDir "../Default/src")

set(DefaultSourceFiles "${DefaultSourceDir}/Dependant.cpp" "${DefaultSourceDir}/Dependant.h" "${DefaultSourceDir}/Dependencies.cpp" "${DefaultSourceDir}/Dependencies.h")

add_executable (2_MockOverride ${DefaultSourceFiles} "src/Mocks.h" "src/Test.cpp" )

include_directories("src/dto" ${dtoInclude})

target_link_libraries(2_MockOverride gtest_main GTest::gmock_main)