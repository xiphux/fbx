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
libfbxaudio_la_SOURCES = AudioFactory.cpp
libfbxaudio_la_LIBADD =
if ALSA
libfbxaudio_la_SOURCES += AudioAlsa.cpp
libfbxaudio_la_LIBADD += @ALSA_LIBS@
endif
if AO
libfbxaudio_la_SOURCES += AudioAo.cpp
libfbxaudio_la_LIBADD += @AO_LIBS@
endif
