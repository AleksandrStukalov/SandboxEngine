cmake_minimum_required(VERSION 3.24)

set(ENGINE_NAME "SandboxEngine")

FILE(GLOB HEADERS include/**.h   include/${ENGINE_NAME}/**.h)
FILE(GLOB SOURCES include/**.cpp include/${ENGINE_NAME}/**.cpp)
add_library(${ENGINE_NAME} STATIC
            ${SOURCES}
            ${HEADERS}
)

target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(${ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

target_include_directories(${ENGINE_NAME} PUBLIC include)
target_include_directories(${ENGINE_NAME} PRIVATE include/${ENGINE_NAME})

set_target_properties(${ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

target_precompile_headers(${ENGINE_NAME}
    PRIVATE
        [["Log.h"]]
)