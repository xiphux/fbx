SUBDIRS = audio audiofile config playlist

AM_CFLAGS = @WX_CFLAGS_ONLY@
AM_CPPFLAGS = @WX_CPPFLAGS@
AM_CXXFLAGS = @WX_CXXFLAGS_ONLY@

bin_PROGRAMS = fbx
fbx_SOURCES = FBXUtil.cpp FBXEngine.cpp FBXAudioThread.cpp PlaylistPanel.cpp FBXFrame.cpp FBX.cpp
fbx_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la config/libfbxconfig.la playlist/libfbxplaylist.la @WX_LIBS@

noinst_PROGRAMS = fbxtest
fbxtest_SOURCES = fbxtest.cpp
fbxtest_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la
