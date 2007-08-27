SUBDIRS = audio audiofile config playlist

AM_CFLAGS = @WX_CFLAGS_ONLY@
AM_CPPFLAGS = @WX_CPPFLAGS@
AM_CXXFLAGS = @WX_CXXFLAGS_ONLY@

bin_PROGRAMS = fbx
fbx_SOURCES = FBXUtil.h FBXUtil.cpp FBXEngine.h FBXEngine.cpp FBXAudioThread.h FBXAudioThread.cpp PlaylistPanel.h PlaylistPanel.cpp FBXFrame.h FBXFrame.cpp FBX.h FBX.cpp
fbx_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la config/libfbxconfig.la playlist/libfbxplaylist.la @WX_LIBS@

check_PROGRAMS = fbxtest
fbxtest_SOURCES = fbxtest.cpp
fbxtest_LDADD = audio/libfbxaudio.la audiofile/libfbxaudiofile.la

EXTRA_DIST = icons/next.xpm icons/pause.xpm icons/play.xpm icons/prev.xpm icons/stop.xpm
