if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR include/cimppy CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package cimppy)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT cimppy_Development
)

install(
    TARGETS cimppy_cimppy
    EXPORT cimppyTargets
    RUNTIME #
    COMPONENT cimppy_Runtime
    LIBRARY #
    COMPONENT cimppy_Runtime
    NAMELINK_COMPONENT cimppy_Development
    ARCHIVE #
    COMPONENT cimppy_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

configure_file(
    cmake/install-config.cmake.in "${package}Config.cmake"
    @ONLY
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    cimppy_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(cimppy_INSTALL_CMAKEDIR)

install(
    FILES
    "${PROJECT_BINARY_DIR}/${package}Config.cmake"
    "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${cimppy_INSTALL_CMAKEDIR}"
    COMPONENT cimppy_Development
)

install(
    EXPORT cimppyTargets
    NAMESPACE cimppy::
    DESTINATION "${cimppy_INSTALL_CMAKEDIR}"
    COMPONENT cimppy_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
