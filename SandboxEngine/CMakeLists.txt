cmake_minimum_required(VERSION 3.24)

set(ENGINE_NAME "SandboxEngine")

FILE(GLOB INCLUDE 
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.cpp"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/**.cpp"
)
FILE(GLOB SRC
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/**.cpp"
)
add_library(${ENGINE_NAME} 
    STATIC
        ${SRC}
        ${INCLUDE}
)

source_group("include" FILES  ${INCLUDE})
source_group("src"     FILES  ${SRC})

target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)

set_target_properties(${ENGINE_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

target_include_directories(${ENGINE_NAME} 
    PUBLIC
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/"
    PRIVATE
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glfw/include/"
)

target_link_directories(${ENGINE_NAME}
    PRIVATE 
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glfw/src/"
)

target_link_libraries(${ENGINE_NAME} glfw)

target_precompile_headers(${ENGINE_NAME}
    PRIVATE
        [["Log.h"]]
)