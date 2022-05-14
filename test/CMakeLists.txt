cmake_minimum_required(VERSION 3.14)

project(cimppyTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
    find_package(cimppy REQUIRED)
    enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(cimppy_test
    source/cimppy_test.cpp
    source/simulation_test.cpp
)
target_link_libraries(
    cimppy_test PRIVATE
    cimppy::cimppy
    Catch2::Catch2WithMain
)
target_compile_features(cimppy_test PRIVATE cxx_std_20)

catch_discover_tests(cimppy_test)

# ---- End-of-file commands ----

add_folders(Test)
