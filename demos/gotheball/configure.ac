AC_INIT([Gotheball], [trunk], [geg@gnu.org])
AC_PREREQ([2.61])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX
AC_LANG([C++])

AC_CANONICAL_HOST
canonical_host=$host

AC_CHECK_HEADER([yase2d.hpp],,
                AC_MSG_ERROR([couldn't find the Yase2D library.]))

#AC_CHECK_LIB([yase2d], [Sound::init],,
#             AC_MSG_ERROR([couldn't find the Yase2D library.]))

AC_CONFIG_FILES([Makefile data/Makefile src/Makefile])
AC_OUTPUT
