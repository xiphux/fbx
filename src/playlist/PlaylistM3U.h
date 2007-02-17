/*
 * PlaylistM3U.h
 * M3U Playlist definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_PLAYLISTM3U_H
#define FBX_PLAYLISTM3U_H

#include "PlaylistBase.h"

#include <fstream>

namespace fbx
{

	class PlaylistM3U: public PlaylistBase
	{
	public:
		PlaylistM3U(const std::string& fname);
		virtual ~PlaylistM3U();
		virtual bool Write();
	protected:
		std::ofstream file;
	};

}

#endif /* FBX_PLAYLISTM3U_H */
