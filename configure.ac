AC_INIT([llvm-demo],[0.0.1],[github@tomlee.co])
AM_INIT_AUTOMAKE([1.9 foreign])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile])

AC_PATH_PROG([LLVMCONFIG],[llvm-config-3.2],[no])
AS_IF([test "x$LLVMCONFIG" = xno],
      [AC_PATH_PROG([LLVMCONFIG],[llvm-config],[no])])
AS_IF([test "x$LLVMCONFIG" = xno],
      [AC_MSG_ERROR([llvm-config not found on your PATH])])
AC_SUBST(LLVM_CXXFLAGS,`$LLVMCONFIG --cxxflags`)
AC_SUBST(LLVM_LIBS,`$LLVMCONFIG --ldflags --libs all | tr '\n' ' '`)

AC_PROG_CXX

AC_OUTPUT

