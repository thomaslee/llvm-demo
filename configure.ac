AC_INIT([llvm-demo],[0.0.1],[github@tomlee.co])
AM_INIT_AUTOMAKE([1.9 foreign])

AC_PATH_PROG([LLVMCONFIG],[llvm-config-2.9],[no])
AS_IF([test "x$LLVMCONFIG" = "xno"],
      [AC_MSG_ERROR([llvm-config-2.9 not found on your PATH])])
AC_SUBST(LLVM_CXXFLAGS,$($LLVMCONFIG --cxxflags))
AC_SUBST(LLVM_LIBS,$($LLVMCONFIG --ldflags --libs engine jit | tr '\n' ' '))

AC_PROG_CXX

AC_OUTPUT([Makefile])

