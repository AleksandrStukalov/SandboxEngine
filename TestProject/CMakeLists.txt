cmake_minimum_required(VERSION 3.24)

set(EXE_NAME "TestProject")

FILE(GLOB SRC 
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/**.cpp"
    "${CMAKE_SOURCE_DIR}/${EXE_NAME}/src/**.h"
)
add_executable(${EXE_NAME}
    ${SRC}
)

source_group("src"  FILES  ${SRC})

target_compile_features(${EXE_NAME} PUBLIC cxx_std_17)
set_target_properties(${EXE_NAME} 
    PROPERTIES
        LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

target_include_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/include/"
)

target_link_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/"
)

target_link_libraries(${EXE_NAME} SandboxEngine)