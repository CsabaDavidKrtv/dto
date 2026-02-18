cmake_minimum_required(VERSION 3.14)

project(3_TemplateHelper_Default)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3_TemplateHelper_Default
    src/3_SimplifiedSyntax.cpp
    src/Dependant.cpp
    src/Dependencies.cpp
)

target_include_directories(3_TemplateHelper_Default
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dto
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ExternalLibraries/dto
)
