dnl
dnl Configuring gauche-gl
dnl  process this file with "autoconf" to generate 'configure'.
dnl

AC_PREREQ(2.54)
AC_INIT(Gauche-gl, 0.6, shiro@acm.org)
AC_CANONICAL_SYSTEM

AC_PATH_XTRA

case "$target" in
  *-*-cygwin*)
    if test "x-$have_x" = "x-disabled" -o "x-$have_x" = "x-no";
    then
      LIBGLUT=glut32;
    else
      LIBGLUT=glut
      CPPFLAGS="$CPPFLAGS -I$x_includes";
    fi;;
  *)
    LIBGLUT=glut;;
esac

# options for configure scripts
GLUT_LIB="-l$LIBGLUT"
AC_ARG_WITH(glut, [  --with-glut[=PATH]:      Use GLUT library installed under PATH.
    By default, Gauche-gl assumes GLUT is installed in the system standard 
    location.  If you do not want to use GLUT support, specify --with-glut=no. 
    On MinGW you can statically link freeglut included in the source.
    If you want to choose so, say --with-glut=mingw-static.], [
  case $with_glut in
    no)  GLUT_LIB= ;;
    yes) GLUT_LIB="-l$LIBGLUT";;
    mingw-static)
         GLUT_LIB="-lfreeglut_static -lgdi32 -lwinmm"
         GLUT_INCDIR="-I../win32/freeglut-3.0.0-1/include -DFREEGLUT_STATIC"
         case "$target" in
	   # MSYS2 config.guess reports x86_64-pc-mingw64 on 64bit system,
	   # but MSYS2/mingw-w64 toolchain canonically use x86_64-w64-mingw32.
           x86_64-*-mingw*)
             GLUT_LIBDIR="-L../win32/freeglut-3.0.0-1/lib/x64";;
           *)
             GLUT_LIBDIR="-L../win32/freeglut-3.0.0-1/lib";;
         esac;;
    *)   GLUT_LIB="-l$LIBGLUT"
         GLUT_INCDIR="-I$with_glut/include"
         GLUT_LIBDIR="-L$with_glut/lib";;
  esac
])

AC_ARG_ENABLE(cg,
   AC_HELP_STRING([--enable-cg], [Enable NVidia's Cg binding.]), [
   AC_DEFINE(HAVE_CG, 1)
   ENABLE_CG=1
   CG_LIBS="-lCgGL -lCg"
   CG_SCM="cg/gl/cg.scm";
])
AC_SUBST(ENABLE_CG)
AC_SUBST(CG_LIBS)
AC_SUBST(CG_SCM)

dnl Set up gauche related commands.  The commands are set by scanning
dnl PATH.  You can override them by "GOSH=/my/gosh ./configure" etc.
AC_PATH_PROG([GOSH], gosh)
AC_PATH_PROG([GAUCHE_CONFIG], gauche-config)
AC_PATH_PROG([GAUCHE_PACKAGE], gauche-package)
AC_PATH_PROG([GAUCHE_INSTALL], gauche-install)
AC_PATH_PROG([GAUCHE_CESCONV], gauche-cesconv)

dnl Usually these parameters are set by AC_PROG_CC, but we'd rather use
dnl the same one as Gauche has been compiled with.
SOEXT=`"$GAUCHE_CONFIG" --so-suffix`
OBJEXT=`"$GAUCHE_CONFIG" --object-suffix`
EXEEXT=`"$GAUCHE_CONFIG" --executable-suffix`
AC_SUBST(SOEXT)
AC_SUBST(OBJEXT)
AC_SUBST(EXEEXT)

# Check for headers
AC_CHECK_HEADERS(GL/glx.h, [   # OpenGL/X11
     # NB: FreeBSD seems to need -lX11 -lXext.  We are on X11 system anyway,
     # so I assume this won't do any harm.
     GL_LIBS='-lGLU -lGL -lX11 -lXext'
     GLUT_LIB="$GLUT_LIB -lXmu -lXi"
], ,)
AC_CHECK_HEADERS(GLUT/glut.h, [
      case $target in
      *-apple-darwin*)  
          AC_DEFINE(MacOSX, 1) # darwin which has GLUT/glut.h is MacOSX
          GL_LIBS='-framework OpenGL -framework GLUT' # GLUT for glutGetProcAddress
          GLUT_LIB='-framework GLUT' ;;
      *)  # other OSes w/o X11 but have GLUT/glut.h. Possibly MacOS9??
      ;;
      esac  
], ,)

if test "$GL_LIBS" = ""; then
  case $target in
    *-*-cygwin*|*-*-mingw*)
      GL_LIBS='-lglu32 -lopengl32' ;;
    *)
      GL_LIBS='-lGLU -lGL' ;;
  esac
fi

# On MinGW, we use GLEW so that we can get newer GL features; the GL header
# comes with MinGW installation is very old.
# TODO: We might add --with-glew configure option so that we can use glew
# on other platforms.  At this moment, though, Gauche-gl has its own
# runtime name lookup system, so having glew isn't vital on other platforms.
case $target in
  *-*-mingw*)
    AC_DEFINE(HAVE_GL_GLEW_H)
    GLEW_INCDIR="-I../win32/glew-1.13.0/include -DGLEW_STATIC"
    GLEW_SOURCE="../win32/glew-1.13.0/src/glew.c"
esac

AC_SUBST(GL_LIBS)
AC_SUBST(GLUT_LIB)
AC_SUBST(GLUT_INCDIR)
AC_SUBST(GLUT_LIBDIR)
AC_SUBST(GLEW_INCDIR)
AC_SUBST(GLEW_SOURCE)

# Check for other programs.
AC_CHECK_PROGS(MAKEINFO, makeinfo)
AC_CHECK_PROGS(GZIP_PROGRAM, gzip)

# Check for libraries

# On Cygwin and MinGW, we need several extra -l flags.
case "$target" in
  *-*-cygwin*|*-*-mingw*)
    # Gauche's uvector library file name was changed in Gauche v0.9.5_pre1.
    GAUCHE_SYSDIR=`"$GAUCHE_CONFIG" --sysarchdir | sed 's/\\\\/\\//g'`
    GAUCHE_UVECTOR_DLL="$GAUCHE_SYSDIR/gauche--uvector.$SOEXT"
    if test -e "$GAUCHE_UVECTOR_DLL"; then
        GAUCHE_UVECTOR_LIBS="-lgauche--uvector"
    else
        GAUCHE_UVECTOR_LIBS="-lgauche-uvector"
    fi
    LIBS="$GAUCHE_UVECTOR_LIBS $LIBS"
    GL_EXTRALIBS="-L. -lgauche-math3d"
    GLUT_EXTRALIBS="-L. -lgauche-gl -lgauche-math3d"
    ;;
esac
AC_SUBST(GL_EXTRALIBS)
AC_SUBST(GLUT_EXTRALIBS)

dnl Creating gpd (gauche package description) file
GAUCHE_PACKAGE_CONFIGURE_ARGS="`echo ""$ac_configure_args"" | sed 's/[\\""\`\$]/\\\&/g'`"
AC_MSG_NOTICE([creating ${PACKAGE_NAME}.gpd])
"$GAUCHE_PACKAGE" make-gpd "$PACKAGE_NAME" \
  -version "$PACKAGE_VERSION" \
  -configure "./configure $GAUCHE_PACKAGE_CONFIGURE_ARGS"

dnl Output
echo $PACKAGE_VERSION > VERSION
AC_OUTPUT(Makefile src/Makefile lib/Makefile cg/Makefile doc/Makefile)
