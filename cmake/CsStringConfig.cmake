#
# Copyright (c) 2017-2022 Barbara Geller
# Copyright (c) 2017-2022 Ansel Sermersheim
#
# This file is part of CsString.
#
# CsString is free software, released under the BSD 2-Clause license.
# For license details refer to LICENSE provided with this project.
#
# CsString is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# https://opensource.org/licenses/BSD-2-Clause
#

if(CsString_FOUND)
   return()
endif()

set(CsString_FOUND TRUE)

# figure out install path
get_filename_component(CsString_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
get_filename_component(CsString_PREFIX ${CsString_CMAKE_DIR}/ ABSOLUTE)

# library dependencies (contains definitions for imported targets)
include("${CsString_CMAKE_DIR}/CsStringLibraryTargets.cmake")

# imported targets INCLUDE_DIRECTORIES
get_target_property(CsString_INCLUDES  CsString::CsString INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(CsString_LIBRARIES CsString::CsString LOCATION)

# export include base dir, imported in other projects
set(CsString_INCLUDE_DIR  "@CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_INCLUDEDIR")
