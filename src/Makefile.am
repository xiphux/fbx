SUBDIRS = audio audiofile

AM_CFLAGS = @WX_CFLAGS_ONLY@
AM_CPPFLAGS = @WX_CPPFLAGS@
AM_CXXFLAGS = @WX_CXXFLAGS_ONLY@

bin_PROGRAMS = fbx
fbx_SOURCES = FBX.cpp
fbx_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la @WX_LIBS@

noinst_PROGRAMS = fbxtest
fbxtest_SOURCES = fbxtest.cpp
fbxtest_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la
