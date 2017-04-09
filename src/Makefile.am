lib_LTLIBRARIES += lib/libCsString.la
lib_libCsString_la_SOURCES =

lib_libCsString_la_CXXFLAGS = $(AM_CXXFLAGS) \
   -I$(top_srcdir)/src \
   -DBUILD_DATE=\"`date +%Y-%m-%d`\"   \
   -DBUILDING_LIB_CS_STRING

lib_libCsString_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined

# library
lib_libCsString_la_SOURCES += src/cs_string.cpp

noinst_HEADERS += src/cs_string.h src/cs_char.h src/cs_string_iterator.h src/cs_encoding.h 


# unit test
check_PROGRAMS = bin/test
bin_test_CXXFLAGS = $(AM_CFLAGS) -I$(top_srcdir)/src -DCS_STRING_ALLOW_UNSAFE

bin_test_SOURCES = test/main.cpp

bin_test_LDADD = lib/libCsString.la

TESTS = bin/test
