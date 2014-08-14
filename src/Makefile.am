bin_PROGRAMS=vsd2svg
if WINDOWS_H
  bin_PROGRAMS += vsd2svg-win
  vsd2svg_win_DEPENDENCIES = @VSD2SVG_WIN_WIN32_RESOURCE@
  vsd2svg_win_SOURCES = vsd2svg-win.cpp
  vsd2svg_win_LDADD = $(libvisio_LIBS) $(librevenge_LIBS) -lcomdlg32 @VSD2SVG_WIN_WIN32_RESOURCE@
  vsd2svg_win_LDFLAGS = -mwindows
endif

AM_CPPFLAGS = $(libvisio_CFLAGS) $(librevenge_CFLAGS) 

vsd2svg_SOURCES = vsd2svg.cpp
vsd2svg_LDADD = $(libvisio_LIBS) $(librevenge_LIBS) 

if WINDOWS_H
@VSD2SVG_WIN_WIN32_RESOURCE@ : vsd2svg-win.rc $(vsd2svg_win_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/compile-resource vsd2svg-win.rc @VSD2SVG_WIN_WIN32_RESOURCE@
endif

EXTRA_DIST = \
	vsd2svg-win.rc.in \
	vsd2svg-win.cpp \
	vsd2svg-win.h
	
BUILD_EXTRA_DIST = \
	vsd2svg-win.rc

