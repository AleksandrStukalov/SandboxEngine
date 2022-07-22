cmake_minimum_required(VERSION 3.24)

set(ENGINE_NAME "SandboxEngine")

FILE(GLOB INCLUDE 
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.cpp"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/**.cpp"
)
FILE(GLOB GLFW
    "${CMAKE_SOURCE_DIR}/SandboxEngine/src/Platform/GLFW/**.h"
    "${CMAKE_SOURCE_DIR}/SandboxEngine/src/Platform/GLFW/**.cpp"
)
FILE(GLOB OPENGL
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Platform/OpenGL/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Platform/OpenGL/**.cpp"
)
FILE(GLOB SRC
    ${GLFW}
    ${OPENGL}
)
add_library(${ENGINE_NAME} 
    STATIC
        ${SRC}
        ${INCLUDE}
)

source_group("src" FILES  ${SRC})
source_group("include" FILES  ${INCLUDE})

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
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glad/include/"
)

target_link_directories(${ENGINE_NAME}
    PRIVATE 
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glfw/src/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glad/"
)

target_link_libraries(${ENGINE_NAME} glfw glad)

target_precompile_headers(${ENGINE_NAME}
    PRIVATE
        [["Log.h"]]
)