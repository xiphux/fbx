AM_CFLAGS =
AM_CXXFLAGS =
if VORBIS
AM_CFLAGS += @VORBISFILE_CFLAGS@
AM_CXXFLAGS += @VORBISFILE_CFLAGS@
endif

noinst_LTLIBRARIES = libfbxaudiofile.la
libfbxaudiofile_la_SOURCES = AudioFileBase.h AudioFileFactory.h AudioFileFactory.cpp
libfbxaudiofile_la_LIBADD =
if VORBIS
libfbxaudiofile_la_SOURCES += AudioFileVorbis.h AudioFileVorbis.cpp
libfbxaudiofile_la_LIBADD += @VORBISFILE_LIBS@
endif
if FLAC
libfbxaudiofile_la_SOURCES += AudioFileFlac.h AudioFileFlac.cpp
libfbxaudiofile_la_LIBADD += @FLAC_LIBS@
endif
if MAGIC
libfbxaudiofile_la_LIBADD += @MAGIC_LIBS@
endif

pkglibaudiofiledir = $(pkglibdir)/audiofile

pkglibaudiofile_LTLIBRARIES =
if VORBIS
pkglibaudiofile_LTLIBRARIES += libvorbis.la
AM_CFLAGS = @VORBISFILE_CFLAGS@
AM_CXXFLAGS = @VORBISFILE_CFLAGS@
libvorbis_la_SOURCES = AudioFileVorbis.h AudioFileVorbis.cpp
libvorbis_la_LDFLAGS = @VORBISFILE_LIBS@ -no-undefined -module -avoid-version
endif

if FLAC
pkglibaudiofile_LTLIBRARIES += libflac.la
AM_CFLAGS =
AM_CXXFLAGS =
libflac_la_SOURCES = AudioFileFlac.h AudioFileFlac.cpp
libflac_la_LDFLAGS = @FLAC_LIBS@ -no-undefined -module -avoid-version
endif
