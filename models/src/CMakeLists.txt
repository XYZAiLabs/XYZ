# Models source CMake configuration
set(MODELS_SOURCES
    model.cpp
    model_loader.cpp
)

set(MODELS_HEADERS
    model.h
    model_loader.h
)

# Create models library
add_library(xyz_models_lib STATIC ${MODELS_SOURCES} ${MODELS_HEADERS})

# Set properties
set_target_properties(xyz_models_lib PROPERTIES
    OUTPUT_NAME "xyz_models"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Include directories
target_include_directories(xyz_models_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/utils
)

# Link dependencies
target_link_libraries(xyz_models_lib
    PUBLIC
        xyz_utils
)

# Installation
install(TARGETS xyz_models_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${MODELS_HEADERS}
    DESTINATION include/xyz/models
)