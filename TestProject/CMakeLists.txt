cmake_minimum_required(VERSION 3.24)

set(EXE_NAME "TestProject")

FILE(GLOB SHADERS
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/shaders/**.vert"
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/shaders/**.frag"
)
FILE(GLOB SRC 
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/**.h"
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/**.cpp"
)
add_executable(${EXE_NAME}
    ${SRC}
    ${SHADERS}
)

source_group("src"  FILES  ${SRC})
source_group("shaders" FILES ${SHADERS})

target_compile_features(${EXE_NAME} PUBLIC cxx_std_17)

target_compile_options(${EXE_NAME} PRIVATE "/W0")

set_target_properties(${EXE_NAME} 
    PROPERTIES
        LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

target_include_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/dependencies/glfw/include/"
        "${CMAKE_SOURCE_DIR}/SandboxEngine/dependencies/glad/include/"
)

target_link_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/"
        "${CMAKE_SOURCE_DIR}/SandboxEngine/dependencies/glfw/src/"
        "${CMAKE_SOURCE_DIR}/SandboxEngine/dependencies/glad/"
)

target_link_libraries(${EXE_NAME} "SandboxEngine" "glfw" "glad")