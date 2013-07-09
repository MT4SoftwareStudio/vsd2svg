#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

m4_define([vsd2svg_version_major],[0])
m4_define([vsd2svg_version_minor],[1])
m4_define([vsd2svg_version_micro],[0])
m4_define([vsd2svg_version],[vsd2svg_version_major.vsd2svg_version_minor.vsd2svg_version_micro])

AC_INIT([vsd2svg], [vsd2svg_version], [sdteffen@sdteffen.de])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_SUBST(V2S_MAJOR_VERSION, [vsd2svg_version_major])
AC_SUBST(V2S_MINOR_VERSION, [vsd2svg_version_minor])
AC_SUBST(V2S_MICRO_VERSION, [vsd2svg_version_micro])
AC_SUBST(V2S_VERSION, [vsd2svg_version])

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_CANONICAL_HOST

AC_MSG_CHECKING([for MinGW])
AS_CASE([$host],
	[*-*-mingw*], [
		native_win32=yes
		VSD2SVG_WIN_WIN32_RESOURCE=vsd2svg-win-win32res.o
	], [
		native_win32=no
		VSD2SVG_WIN_WIN32_RESOURCE=
	]
)
AC_MSG_RESULT([$native_win32])
AM_CONDITIONAL(OS_WIN32, [test "x$native_win32" = "xyes"])
AC_SUBST(VSD2SVG_WIN_WIN32_RESOURCE)

AS_IF([test "x$native_win32" = "xyes"], [
	AC_CHECK_TOOL(WINDRES, windres)
])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile build/Makefile build/win32/Makefile \
	data/Makefile data/icons/Makefile \
	data/icons/16x16/Makefile data/icons/32x32/Makefile \
	data/icons/48x48/Makefile data/icons/256x256/Makefile \
	installer/Makefile installer/macosx/Makefile \
	installer/rpm/Makefile src/vsd2svg-win.rc\
	src/Makefile])

# Checks for libraries.
PKG_CHECK_MODULES([libvisio],[libvisio-0.0])

# Checks for header files.
AC_CHECK_HEADERS([windows.h], [AM_CONDITIONAL([WINDOWS_H], true)], 
	[AM_CONDITIONAL([WINDOWS_H], false)])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT

