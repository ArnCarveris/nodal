# The MIT License (MIT)
#
# Copyright (c) 2015 Fabio Massaioli
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.0)
project(nodal VERSION 0.1.0 LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(EnableCXX11)
include(ConfigureSourceDefinitions)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(Boost REQUIRED)

option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

set(SOURCES
  src/compiler.cpp
  src/graph.cpp
  src/graph_link.cpp
  src/graph_node.cpp
)

set(HEADERS
  include/nodal/any.h
  include/nodal/compiler.h
  include/nodal/graph.h
  include/nodal/graph_link.h
  include/nodal/graph_node.h
  include/nodal/node.h
  include/nodal/node_data.h

  include/nodal/detail/graph_access.h
  include/nodal/detail/graph_properties.h
  include/nodal/detail/link_list.h
)

configure_source_definitions(
  "__NODAL_BUILDING_@id@__"
  BASE_PATH "src"
  ${SOURCES})

add_library(nodal ${SOURCES} ${HEADERS})

enable_cxx11(nodal)
target_include_directories(
  nodal PRIVATE "include/nodal" "src" ${Boost_INCLUDE_DIRS})

set_target_properties(nodal PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}")

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS nodal EXPORT nodal
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(EXPORT nodal
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/nodal"
        FILE "nodal-targets.cmake")

configure_package_config_file(
  "nodal-config.cmake.in" "${PROJECT_BINARY_DIR}/nodal-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/nodal"
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/nodal-config-version.cmake"
  COMPATIBILITY SameMajorVersion)

install(FILES "${PROJECT_BINARY_DIR}/nodal-config.cmake"
              "${PROJECT_BINARY_DIR}/nodal-config-version.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/nodal")