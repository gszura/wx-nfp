# Process this file with autoconf to produce a configure script.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_PREREQ([2.64])
AC_INIT([wx-nfp], [0.9.1], [grzegorz@szura.net])
AC_CONFIG_SRCDIR([src/wx-nfpApp.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_GNU_SOURCE

# Checks for libraries.
AM_OPTIONS_WXCONFIG
reqwx=2.8.7
AM_PATH_WXCONFIG($reqwx, wxWin=1)
if test "$wxWin" != 1; then
AC_MSG_ERROR([
wxWidgets must be installed on your system.
 
Please check that wx-config is in path, the directory
where wxWidgets libraries are installed (returned by
'wx-config --libs' or 'wx-config --static --libs' command)
is in LD_LIBRARY_PATH or equivalent variable and
wxWidgets version is $reqwx or above.
])
fi
 
CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY"
CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
LDFLAGS="$LDFLAGS $WX_LIBS"
LIBS="$LIBS $WX_LIBS"

#AC_DEFUN([AC_DATAROOTDIR_CHECKED])
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18])

AC_CONFIG_FILES([Makefile po/Makefile.in
src/Makefile
data/Makefile
data/icons/Makefile
data/icons/16x16/Makefile
data/icons/22x22/Makefile
data/icons/24x24/Makefile
data/icons/32x32/Makefile
data/icons/48x48/Makefile
doc/Makefile
doc/html/Makefile
doc/html/img/Makefile
doc/html/pl/Makefile
doc/html/en/Makefile])

AC_OUTPUT

# include/Makefile


