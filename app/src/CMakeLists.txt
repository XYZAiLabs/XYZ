# Application source CMake configuration
set(APP_SOURCES
    app_main.cpp
    app_manager.cpp
)

set(APP_HEADERS
    app_manager.h
)

# Create the main application executable
add_executable(xyz_app ${APP_SOURCES} ${APP_HEADERS})

# Include directories
target_include_directories(xyz_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils
)

# Link dependencies
target_link_libraries(xyz_app PRIVATE
    xyz_agents_lib
    xyz_utils
    pthread
)

# Set compile options
target_compile_options(xyz_app PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:DEBUG>:-g -O0>
    $<$<CONFIG:RELEASE>:-O3>
)

# Set properties
set_target_properties(xyz_app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS xyz_app
    RUNTIME DESTINATION bin
)