/*
 * PlaylistFactory.cpp
 * Playlist Factory implementation
 * Copyright (C) 2007 Christopher Han
 */

#include "PlaylistFactory.h"

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
