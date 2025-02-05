# Examples CMake configuration
cmake_minimum_required(VERSION 3.12)

# Set C++ standard for examples
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create example executables
add_executable(example_1 example_1.cpp)
add_executable(example_2 example_2.cpp)

# Include directories
target_include_directories(example_1 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/agents/src
    ${CMAKE_SOURCE_DIR}/utils
)

target_include_directories(example_2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/agents/src
    ${CMAKE_SOURCE_DIR}/utils
)

# Link dependencies
target_link_libraries(example_1 PRIVATE
    xyz_agents_lib
    xyz_utils
    pthread
)

target_link_libraries(example_2 PRIVATE
    xyz_agents_lib
    xyz_utils
    pthread
)

# Set compile options
foreach(target example_1 example_2)
    target_compile_options(${target} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:DEBUG>:-g -O0>
        $<$<CONFIG:RELEASE>:-O3>
    )
endforeach()

# Installation
install(TARGETS example_1 example_2
    RUNTIME DESTINATION bin/examples
)