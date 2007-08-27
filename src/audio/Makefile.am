AM_CFLAGS =
AM_CXXFLAGS =
if ALSA
AM_CFLAGS += @ALSA_CFLAGS@
AM_CXXFLAGS += @ALSA_CFLAGS@
endif
if AO
AM_CFLAGS += @AO_CFLAGS@
AM_CXXFLAGS += @AO_CFLAGS@
endif

noinst_LTLIBRARIES = libfbxaudio.la
libfbxaudio_la_SOURCES = AudioBase.h AudioFactory.h AudioFactory.cpp
libfbxaudio_la_LIBADD =
if ALSA
libfbxaudio_la_SOURCES += AudioAlsa.h AudioAlsa.cpp
libfbxaudio_la_LIBADD += @ALSA_LIBS@
endif
if AO
libfbxaudio_la_SOURCES += AudioAo.h AudioAo.cpp
libfbxaudio_la_LIBADD += @AO_LIBS@
endif

pkglibaudiodir = $(pkglibdir)/audio

pkglibaudio_LTLIBRARIES =
if ALSA
pkglibaudio_LTLIBRARIES += libalsa.la
AM_CFLAGS = @ALSA_CFLAGS@
AM_CXXFLAGS = @ALSA_CFLAGS@
libalsa_la_SOURCES = AudioAlsa.h AudioAlsa.cpp
libalsa_la_LDFLAGS = @ALSA_LIBS@ -no-undefined -module -avoid-version
endif

if AO
pkglibaudio_LTLIBRARIES += libao.la
AM_CFLAGS = @AO_CFLAGS@
AM_CXXFLAGS = @AO_CFLAGS@
libao_la_SOURCES = AudioAo.h AudioAo.cpp
libao_la_LDFLAGS = @AO_LIBS@ -no-undefined -module -avoid-version
endif
