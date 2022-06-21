#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([tuttepoly],[v0.9.19],[david.pearce@ecs.victoria.ac.nz])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([tutte/tutte.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

# Checks for GNU Multiple Precision (GMP) library.
# AC_CHECK_LIB([gmp], [__gmpz_add])
# AC_CHECK_LIB([gmpxx], [main]) # use special symbol "main" as I don't know about to resolve name mangling.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stddef.h unistd.h sys/types.h stdlib.h string.h errno.h])

# Checks for typedefs, structures, and compiler characteristics.

AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
m4_warn([obsolete],
[Update your code to rely only on HAVE_SYS_TIME_H,
then remove this warning and the obsolete code below it.
All current systems provide time.h; it need not be checked for.
Not all systems provide sys/time.h, but those that do, all allow
you to include it and time.h simultaneously.])dnl
AC_CHECK_HEADERS_ONCE([sys/time.h])
# Obsolete code to be removed.
if test $ac_cv_header_sys_time_h = yes; then
  AC_DEFINE([TIME_WITH_SYS_TIME],[1],[Define to 1 if you can safely include both <sys/time.h>
	     and <time.h>.  This macro is obsolete.])
fi
# End of obsolete code.

AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

AC_CHECK_SIZEOF([unsigned int *])
AC_CHECK_SIZEOF(int,4)
AC_SUBST(ac_cv_sizeof_int)
AC_CHECK_SIZEOF(long,4)
AC_SUBST(ac_cv_sizeof_long)
AC_CHECK_SIZEOF(long long,0)
AC_SUBST(ac_cv_sizeof_long_long)


# Checks for library functions.
AC_FUNC_MALLOC
m4_warn([obsolete],
[The preprocessor macro `STDC_HEADERS' is obsolete.
  Except in unusual embedded environments, you can safely include all
  ISO C90 headers unconditionally.])dnl
# Autoupdate added the next two lines to ensure that your configure
# script's behavior did not change.  They are probably safe to remove.
AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

AC_CHECK_FUNCS([alarm gettimeofday memmove memset pow sqrt strtol])

AC_CONFIG_FILES([makefile
                 nauty/makefile
		 tutte/makefile])
AC_OUTPUT
