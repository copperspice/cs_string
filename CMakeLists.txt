cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

cmake_policy(VERSION 3.8..3.20)

# support using rpath on Mac OS X
cmake_policy(SET CMP0042 NEW)

project(cs_string)

set(BUILD_MAJOR "1")
set(BUILD_MINOR "3")
set(BUILD_MICRO "1")

set(BUILD_COMPONENTS "cs_string")

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)

# file locations for installing
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
   include(GNUInstallDirs)
   set(CMAKE_INSTALL_RPATH "@executable_path")

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")
   include(GNUInstallDirs)
   set(CMAKE_INSTALL_RPATH "\$ORIGIN")

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   set(CMAKE_INSTALL_BINDIR bin)
   set(CMAKE_INSTALL_LIBDIR lib)
   set(CMAKE_INSTALL_INCLUDEDIR include)

endif()

set(PACKAGE               "cs_string")
set(PACKAGE_NAME          "CsString")
set(PACKAGE_VERSION       "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_STRING        "cs_string ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_MICRO}")
set(PACKAGE_TARNAME       "cs_string")
set(PACKAGE_BUGREPORT     "info@copperspice.com")
set(PACKAGE_URL           "https://www.copperspice.com/")

set(CPACK_PACKAGE_NAME    ${PROJECT_NAME} )
set(CPACK_PACKAGE_VENDOR  "CopperSpice")
set(CPACK_PACKAGE_CONTACT "info@copperspice.com")

set(CPACK_PACKAGE_VERSION_MAJOR ${BUILD_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${BUILD_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${BUILD_MICRO})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Unicode aware string library")
set(CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_IGNORE_FILES         "/build/;/.git;${CPACK_SOURCE_IGNORE_FILES}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY   ${CMAKE_INSTALL_PREFIX})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY  OFF)

include(CPack)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
   set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -Wl,-undefined,error")
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,error")
   set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-undefined,error")

elseif(CMAKE_SYSTEM_NAME MATCHES "(OpenBSD|FreeBSD|NetBSD|DragonFly)")
   set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -Wl,--no-undefined")
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ")
   set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")

elseif(MSVC)
   string (REGEX REPLACE "/W3" "" CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}"  )
   string (REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

   add_compile_options("/utf-8")

else()
   # Linux, Windows (MinGW)

   set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -Wl,--no-undefined")
   set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
   set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")
endif()

# file locations for building
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(src/string.cmake)
include(test/test.cmake)
