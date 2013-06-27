bin_PROGRAMS=vsd2svg
if WINDOWS_H
  bin_PROGRAMS += vsd2svg-win
  vsd2svg_win_SOURCES = vsd2svg-win.cpp
  vsd2svg_win_LDADD = $(libvisio_LIBS) -lcomdlg32
endif

AM_CPPFLAGS = $(libvisio_CFLAGS)

vsd2svg_SOURCES = vsd2svg.cpp
vsd2svg_LDADD = $(libvisio_LIBS)

