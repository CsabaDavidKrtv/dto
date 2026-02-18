cmake_minimum_required(VERSION 3.14)

project(3_TemplateHelper_Override)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use sources from Default project
add_executable(3_TemplateHelper_Override
    ${CMAKE_CURRENT_SOURCE_DIR}/../Default/src/3_TemplateHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Default/src/Dependant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Default/src/Dependencies.cpp
)

# Use Override's dto folder, not Default's
target_include_directories(3_TemplateHelper_Override
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dto
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ExternalLibraries/dto
)
