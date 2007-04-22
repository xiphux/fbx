AM_CFLAGS =
AM_CXXFLAGS =
if VORBIS
AM_CFLAGS += @VORBISFILE_CFLAGS@
AM_CXXFLAGS += @VORBISFILE_CFLAGS@
endif

noinst_LTLIBRARIES = libfbxaudiofile.la
libfbxaudiofile_la_SOURCES = AudioFileBase.h AudioFileBase.cpp AudioFileFactory.h AudioFileFactory.cpp
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
