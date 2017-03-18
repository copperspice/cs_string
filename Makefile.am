AUTOMAKE_OPTIONS = subdir-objects nostdinc
ACLOCAL_AMFLAGS = -I autotools/m4 --install
AM_CFLAGS =  -DQT_SHARED
AM_CXXFLAGS = $(AM_CFLAGS)

# for objective c, used to turn on c++11
OBJCXXFLAGS = $(CXXFLAGS)

AM_LDFLAGS =
bin_PROGRAMS=
BUILT_SOURCES =
CLEANFILES =
noinst_HEADERS =
noinst_LTLIBRARIES =
lib_LTLIBRARIES =
EXTRA_LTLIBRARIES =
EXTRA_DIST=LICENSE

# Do not alter lines above this comment
include src/Makefile.am

#
DISTCLEANFILES = .version.cpp .version.o .build-stamp-*

# Tag the distribution
dist-hook:
	echo $(VERSION) > $(distdir)/autotools/.tarball-version	
	find $(distdir) -name qrc_\*.cpp -exec rm -f '{}' ';'

windows-zip: distdir
	-rm -f $(distdir).zip
	(cd $(distdir) && zip -rq ../$(distdir).zip .)
	$(am__remove_distdir)

# Stamp the build with the correct version
.version.cpp: .build-stamp-$(VERSION)
	echo 'const char* cs_string_version = "cs_string $(VERSION)";' > .version.cpp

.build-stamp-$(VERSION):
	@rm -f .build-stamp*
	@touch $@