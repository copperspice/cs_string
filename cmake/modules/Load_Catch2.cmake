# ***********************************************************************
#
# Copyright (c) 2017-2024 Barbara Geller
# Copyright (c) 2017-2024 Ansel Sermersheim
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
# ***********************************************************************

find_package(Catch2 QUIET)

if (NOT TARGET Catch2::Catch2)
   message(STATUS "Catch2 was not found, CsString unit tests will not be built\n")
   return()
endif()
