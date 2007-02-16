SUBDIRS = audiofile

AM_CFLAGS = @WX_CFLAGS_ONLY@
AM_CPPFLAGS = @WX_CPPFLAGS@
AM_CXXFLAGS = @WX_CXXFLAGS_ONLY@

bin_PROGRAMS = fbx
fbx_SOURCES = FBX.cpp
fbx_LDADD = audiofile/libfbxaudiofile.la @WX_LIBS@
