add_executable(Test "")

target_compile_definitions(
   Test
   PRIVATE
   -DCS_STRING_ALLOW_UNSAFE
)

target_sources(Test
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
)

target_link_libraries(Test
   PRIVATE
   CsString
)
