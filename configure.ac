#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([vsd2svg], [0.1.0], [sdteffen@sdteffen.de])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile installer/Makefile installer/macosx/Makefile \
	installer/rpm/Makefile \
	src/Makefile])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_CHECK_MODULES([libvisio],[libvisio-0.0])

# Checks for header files.
AC_CHECK_HEADERS([windows.h], [AM_CONDITIONAL([WINDOWS_H], true)], 
	[AM_CONDITIONAL([WINDOWS_H], false)])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT

