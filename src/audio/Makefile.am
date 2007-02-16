AM_CFLAGS = @ALSA_CFLAGS@ @AO_CFLAGS@
AM_CXXFLAGS = @ALSA_CFLAGS@ @AO_CFLAGS@

noinst_LTLIBRARIES = libfbxaudio.la
libfbxaudio_la_SOURCES = AudioFactory.cpp AudioAlsa.cpp AudioAo.cpp
libfbxaudio_la_LIBADD = @ALSA_LIBS@ @AO_LIBS@
