AM_CFLAGS =
AM_CXXFLAGS =
if VORBIS
AM_CFLAGS += @VORBISFILE_CFLAGS@
AM_CXXFLAGS += @VORBISFILE_CFLAGS@
endif

noinst_LTLIBRARIES = libfbxaudiofile.la
libfbxaudiofile_la_SOURCES = AudioFileBase.cpp AudioFileFactory.cpp
libfbxaudiofile_la_LIBADD =
if VORBIS
libfbxaudiofile_la_SOURCES += AudioFileVorbis.cpp
libfbxaudiofile_la_LIBADD += @VORBISFILE_LIBS@
endif
