AC_INIT([cs_string], [1.0.0], [info@copperspice.com])

# derive CS hex version from "@PACKAGE_VERSION@"
HEX_VERSION=$(printf "0x%02x%02x%02x" `echo $PACKAGE_VERSION | tr '.' ' '`)
AC_SUBST([HEX_VERSION])

AC_CONFIG_AUX_DIR([autotools/build-aux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_SYS_LARGEFILE

AC_CONFIG_SRCDIR([src/cs_string.h])
AM_INIT_AUTOMAKE([foreign tar-pax])

LT_INIT([win32-dll disable-static])

AM_PROG_CC_C_O
AC_PROG_CXX

# set flags for c++11
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext])

case "$target" in
*-*-mingw*)
	OSTYPE=WIN ;;
*-*-linux-*)
	OSTYPE=LINUX ;;
*-*-darwin*)
	OSTYPE=DARWIN ;;
*-*-*bsd*)
	OSTYPE=BSD ;;
esac

AC_CHECK_SIZEOF(size_t)

case "$ac_cv_sizeof_size_t" in
4)
	OSTYPE_DISPLAY=$OSTYPE"-32" ;;
8)
	OSTYPE_DISPLAY=$OSTYPE"-64" ;;
*)
	OSTYPE_DISPLAY=$OSTYPE"-unknown";;
esac

AC_PROG_OBJCXX

# not mandatory
echo ""

AM_CONDITIONAL(OSTYPE_WIN, test "$OSTYPE" == WIN)
AM_CONDITIONAL(OSTYPE_LINUX, test "$OSTYPE" == LINUX)
AM_CONDITIONAL(OSTYPE_DARWIN, test "$OSTYPE" == DARWIN)
AM_CONDITIONAL(OSTYPE_BSD, test "$OSTYPE" == BSD)

real_dir_name()
{
eval realdir=${1}
eval realdir=${realdir}
eval realdir=${realdir}
}

echo
echo "CsString configured to run on:     " $OSTYPE_DISPLAY
echo "CsString will be built in:         " `pwd`
echo "CsString will be installed in:     " ${prefix}
echo
echo "CsString is now configured"

AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIR([autotools/m4])
AC_OUTPUT
