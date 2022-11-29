# ***********************************************************************
#
# Copyright (c) 2017-2022 Barbara Geller
# Copyright (c) 2017-2022 Ansel Sermersheim
#
# This file is part of CsString.
#
# CsString is free software. You can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# CsString is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# https://www.gnu.org/licenses/
#
# ***********************************************************************

find_package(Catch2 QUIET)

if (NOT TARGET Catch2::Catch2)
   message(STATUS "Catch2 was not found, CsString unit tests will not be built\n")
   return()
endif()
