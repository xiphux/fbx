/**
 * @file PlaylistFactory.cpp
 * @brief Playlist Factory implementation
 * @author Christopher Han
 *
 * Playlist Factory and utility class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#include "PlaylistFactory.h"
#include "PlaylistM3U.h"

/**
 * Tests whether a given playlist filename is a recognized playlist format
 */
bool fbx::playlist::PlaylistFactory::IsPlaylist(const std::string& filename)
{
	return (PlaylistType(filename) > FBX_PLAYLIST_NONE);
}

/**
 * Attempts to determine the format of the given playlist
 */
unsigned int fbx::playlist::PlaylistFactory::PlaylistType(const std::string& filename)
{
	std::string::size_type pos = filename.find_last_of('.');
	std::string ext = filename.substr(pos+1);
	if (ext == "m3u")
		return FBX_PLAYLIST_M3U;
	else if (ext == "pls")
		return FBX_PLAYLIST_PLS;
	return FBX_PLAYLIST_NONE;
}

/**
 * Attempts to open a given playlist, and returns a typed playlist instance
 * appropriate for the given playlist
 */
fbx::playlist::PlaylistBase* fbx::playlist::PlaylistFactory::OpenPlaylist(const std::string& filename)
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

/**
 * Attempts to transform an original playlist of one type into a new type based on
 * the given filename for it
 * (Usually used to transform untyped in-memory playlists into a typed format when
 * saving it to a specific file)
 */
fbx::playlist::PlaylistBase* fbx::playlist::PlaylistFactory::ChangePlaylistType(fbx::playlist::PlaylistBase* orig, std::string fname)
{
	if (!orig)
		return 0;
	PlaylistBase* newpls = OpenPlaylist(fname);
	if (!newpls)
		return 0;
	newpls->playlist = orig->playlist;
	return newpls;
}
