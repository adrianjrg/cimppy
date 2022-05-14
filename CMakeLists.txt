cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    cimppy
    VERSION 0.1.0
    DESCRIPTION "C++ implementation of simpy."
    HOMEPAGE_URL "https://git.adrianguillot.com/adriang/cimppy"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(cimppy_cimppy
    source/cimppy.cpp
    source/events.cpp
    source/simulation.cpp
)
add_library(cimppy::cimppy ALIAS cimppy_cimppy)

include(GenerateExportHeader)
generate_export_header(
    cimppy_cimppy
    BASE_NAME cimppy
    EXPORT_FILE_NAME export/cimppy/cimppy_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(cimppy_cimppy PUBLIC CIMPPY_STATIC_DEFINE)
endif()

set_target_properties(
    cimppy_cimppy PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME cimppy
    OUTPUT_NAME cimppy
)

target_include_directories(
    cimppy_cimppy ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    cimppy_cimppy SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(cimppy_cimppy PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(cimppy_cimppy PRIVATE fmt::fmt)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT cimppy_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
        AUTHOR_WARNING
        "Developer mode is intended for developers of cimppy"
    )
endif()

include(cmake/dev-mode.cmake)
