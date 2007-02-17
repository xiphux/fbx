/*
 * PlaylistFactory.cpp
 * Playlist Factory implementation
 * Copyright (C) 2007 Christopher Han
 */

#include "PlaylistFactory.h"
#include "PlaylistM3U.h"

bool fbx::PlaylistFactory::IsPlaylist(const std::string& filename)
{
	return (PlaylistType(filename) > FBX_PLAYLIST_NONE);
}

unsigned int fbx::PlaylistFactory::PlaylistType(const std::string& filename)
{
	std::string::size_type pos = filename.find_last_of('.');
	std::string ext = filename.substr(pos+1);
	if (ext == "m3u")
		return FBX_PLAYLIST_M3U;
	else if (ext == "pls")
		return FBX_PLAYLIST_PLS;
	return FBX_PLAYLIST_NONE;
}

fbx::PlaylistBase* fbx::PlaylistFactory::OpenPlaylist(const std::string& filename)
{
	unsigned int type = PlaylistType(filename);
	switch (type) {
		case FBX_PLAYLIST_M3U:
			return new PlaylistM3U(filename);
#if 0
		case FBX_PLAYLIST_PLS:
			return new PlaylistPLS(filename);
#endif
	}
	return 0;
}

fbx::PlaylistBase* fbx::PlaylistFactory::ChangePlaylistType(fbx::PlaylistBase* orig, std::string fname)
{
	if (!orig)
		return 0;
	PlaylistBase* newpls = OpenPlaylist(fname);
	if (!newpls)
		return 0;
	newpls->playlist = orig->playlist;
	return newpls;
}
