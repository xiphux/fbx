/*
 * PlaylistFactory.h
 * Playlist Factory definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_PLAYLISTFACTORY_H
#define FBX_PLAYLISTFACTORY_H

#include "PlaylistBase.h"

namespace fbx
{

	class PlaylistFactory
	{
	public:
		static bool IsPlaylist(const std::string& filename);
		static unsigned int PlaylistType(const std::string& filename);
	};

}

#endif /* FBX_PLAYLISTFACTORY_H */
