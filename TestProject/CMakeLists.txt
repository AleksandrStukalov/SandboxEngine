cmake_minimum_required(VERSION 3.24)

set(EXE_NAME "TestProject")


FILE(GLOB SOURCES src/**.cpp)
FILE(GLOB HEADERS src/**.h)
add_executable(${EXE_NAME}
                ${SOURCES}
                ${HEADERS}
)

set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

target_compile_features(${EXE_NAME} PUBLIC cxx_std_17)
set_target_properties(${EXE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/include"
)

target_link_directories(${EXE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SandboxEngine/Debug"
        "${CMAKE_SOURCE_DIR}/SandboxEngine/Release"
)

target_link_libraries(${EXE_NAME} SandboxEngine)