cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME "SandboxEngine")
project(${PROJECT_NAME})

set(CMAKE_SUPPRESS_REGENERATION true) # Gets rid of ZERO_CHECK

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

add_subdirectory(SandboxEngine)
add_subdirectory(TestProject)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TestProject)