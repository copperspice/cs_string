include(Load_Catch2)
include(CTest)

add_executable(CsStringTest "")
set_target_properties(CsStringTest
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.12.0")
   set_target_properties(CsStringTest
      PROPERTIES

      # only a request for C++20
      CXX_STANDARD_REQUIRED OFF
      CXX_STANDARD 20
   )
endif()

file(WRITE ${CMAKE_BINARY_DIR}/bin/test/run_test.bat
   "@SET PATH=..;%PATH%\n@CsStringTest\n"
)

target_link_libraries(CsStringTest
   PUBLIC
   CsString
   Catch2::Catch2
)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(CsStringTest
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/cs_catch2.h

   ${CMAKE_CURRENT_SOURCE_DIR}/cs_string.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(CsStringTest)
