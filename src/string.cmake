add_library(CsString SHARED "")

target_compile_definitions(
   CsString
   PRIVATE
   -DBUILDING_LIB_CS_STRING
)

target_compile_features(
   CsString
   PUBLIC
   cxx_std_17
)

target_include_directories(
   CsString
   PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_sources(CsString
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_string.cpp
)

set(CS_STRING_INCLUDE
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_char.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_encoding.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_string.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_string_iterator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/cs_string_view.h
)

install(
   TARGETS CsString
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
   FILES ${CS_STRING_INCLUDE}
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
   COMPONENT Devel
)

