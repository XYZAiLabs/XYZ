# Agents module CMake configuration
set(AGENTS_SOURCES
    base_agent.cpp
    ai_processor.cpp
    agent_manager.cpp
    utils.cpp
    main.cpp
)

set(AGENTS_HEADERS
    base_agent.h
    ai_processor.h
    agent_manager.h
    utils.h
)

# Create the agents executable
add_executable(xyz_agents ${AGENTS_SOURCES} ${AGENTS_HEADERS})

# Include directories
target_include_directories(xyz_agents PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils
)

# Link dependencies
target_link_libraries(xyz_agents PRIVATE
    xyz_utils
    jsoncpp
    pthread
)

# Installation
install(TARGETS xyz_agents
    RUNTIME DESTINATION bin
)

# Set compile options
target_compile_options(xyz_agents PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:DEBUG>:-g -O0>
    $<$<CONFIG:RELEASE>:-O3>
)

# Set properties
set_target_properties(xyz_agents PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)