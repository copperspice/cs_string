cmake_minimum_required(VERSION 3.14)

project(CsString LANGUAGES CXX VERSION 1.2.1)

add_library(cs_string INTERFACE)
target_include_directories(cs_string INTERFACE src)
target_compile_features(cs_string INTERFACE cxx_std_14)

file(GLOB SOURCES src/*.cpp)

add_executable(cs_string_test test/main.cpp)
target_link_libraries(cs_string_test cs_string)

# TODO: Remove the need for this
target_compile_definitions(cs_string_test PRIVATE CS_STRING_ALLOW_UNSAFE)
