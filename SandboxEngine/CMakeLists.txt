cmake_minimum_required(VERSION 3.24)

set(ENGINE_NAME "SandboxEngine")

FILE(GLOB INCLUDE 
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/**.cpp"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/Graphics/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/Graphics/Primitives/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/Window/**.h"
)
FILE(GLOB GLFW
    "${CMAKE_SOURCE_DIR}/SandboxEngine/src/Window/GLFW/**.h"
    "${CMAKE_SOURCE_DIR}/SandboxEngine/src/Window/GLFW/**.cpp"
)
FILE(GLOB OPENGL
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Graphics/OpenGL/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Graphics/OpenGL/**.cpp"
)
FILE(GLOB IMGUI
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/imgui/**.h"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/imgui/**.cpp"
)
FILE(GLOB SRC
    ${GLFW}
    ${OPENGL}
    ${IMGUI}
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/**.txt"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Graphics/shaders/**.vert"
    "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/Graphics/shaders/**.frag"
)
add_library(${ENGINE_NAME} 
    STATIC
        ${SRC}
        ${INCLUDE}
)

source_group("src" FILES  ${SRC})
source_group("include" FILES  ${INCLUDE})

target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)

target_compile_options(${ENGINE_NAME} PRIVATE "/W0")

set_target_properties(${ENGINE_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

target_include_directories(${ENGINE_NAME} 
    PUBLIC
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/imgui/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glm/"
    PRIVATE
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include/${ENGINE_NAME}/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glfw/include/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glad/include/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/stb/"
)

target_link_directories(${ENGINE_NAME}
    PRIVATE 
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glfw/src/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glad/"
        "${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/dependencies/glm/"
)

target_link_libraries(${ENGINE_NAME} "glfw" "glad" "glm")

target_precompile_headers(${ENGINE_NAME}
    PRIVATE
        [["Log.h"]]
        [["Window/Input.h"]]
        [["Graphics/Types.h"]]
        
        # NOTE: 
        # Header file names specified with angle brackets (e.g. <unordered_map>) or explicit double quotes, e.g. [["other_header.h"]]) will be treated as is,  and include directories must be available for the compiler to find them. 
        # Other header file names (e.g. project_header.h) are interpreted as being relative to the current source directory (e.g. CMAKE_CURRENT_SOURCE_DIR) and will be included by absolute path. 
)