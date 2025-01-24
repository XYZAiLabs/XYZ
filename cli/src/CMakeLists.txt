# CLI source CMake configuration
set(CLI_SOURCES
    cli_main.cpp
    cli_manager.cpp
)

set(CLI_HEADERS
    cli_manager.h
)

# Create the CLI executable
add_executable(xyz_cli ${CLI_SOURCES} ${CLI_HEADERS})

# Include directories
target_include_directories(xyz_cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils
)

# Link dependencies
target_link_libraries(xyz_cli PRIVATE
    xyz_utils
    xyz_agents_lib
    pthread
)

# Set compile options
target_compile_options(xyz_cli PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:DEBUG>:-g -O0>
    $<$<CONFIG:RELEASE>:-O3>
)

# Set properties
set_target_properties(xyz_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)