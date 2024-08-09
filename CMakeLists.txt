cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME "SandboxEngine")
project(${PROJECT_NAME})

set(CMAKE_SUPPRESS_REGENERATION true) # Gets rid of ZERO_CHECK

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

add_subdirectory(SandboxEngine)
add_subdirectory(TestProject)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TestProject)
set(CMAKE_CXX_FLAGS "-std=c++20")

# Updating submodules when configuring:
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/SandboxEngine/dependencies/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded. Please, update submodules and try again.")
endif()

add_subdirectory("SandboxEngine/dependencies/glfw")
add_subdirectory("SandboxEngine/dependencies/glad")
add_subdirectory("SandboxEngine/dependencies/glm")