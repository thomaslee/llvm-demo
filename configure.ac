AC_INIT([llvm-demo],[0.0.1],[github@tomlee.co])
AM_INIT_AUTOMAKE([1.9 foreign])

LLVMVERSION_MINIMUM=3.2

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile])

AC_PATH_PROG([LLVMCONFIG_VER],[llvm-config-$LLVMVERSION_MINIMUM],[no])
AS_IF([test "x$LLVMCONFIG_VER" = xno],
      [AC_PATH_PROG([LLVMCONFIG],[llvm-config],[no])],
      [LLVMCONFIG=$LLVMCONFIG_VER])
AS_IF([test "x$LLVMCONFIG" = xno],
      [AC_MSG_ERROR([llvm-config not found on your PATH])])

AC_MSG_CHECKING([llvm version])
LLVMVERSION=`$LLVMCONFIG --version`
AC_MSG_RESULT([$LLVMVERSION])
AS_IF([test "x$LLVMVERSION" \< "x$LLVMVERSION_MINIMUM"],
      [AC_MSG_RESULT([llvm v$LLVMVERSION is less than required minimum: $LLVMVERSION_MINIMUM])])

AC_SUBST(LLVM_CXXFLAGS,`$LLVMCONFIG --cxxflags`)
AC_SUBST(LLVM_LIBS,`$LLVMCONFIG --ldflags --libs all | tr '\n' ' '`)

AC_PROG_CXX

AC_OUTPUT

