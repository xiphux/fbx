/*
 * PlaylistBase.h
 * Base Playlist definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_PLAYLISTBASE_H
#define FBX_PLAYLISTBASE_H

#define FBX_PLAYLIST_NONE 0
#define FBX_PLAYLIST_M3U 1
#define FBX_PLAYLIST_PLS 2

#include <string>
#include <vector>

namespace fbx
{

	class PlaylistBase
	{
	public:
		PlaylistBase(const std::string& fname);
		virtual ~PlaylistBase();
		virtual bool Write();
		std::string Current();
		bool Prev();
		bool Next();
		unsigned int Size();
		std::string GetPath();
		std::string GetFilename() const;
		void SetFilename(const std::string& name);
		void Append(const std::string& f);
	protected:
		std::string filename;
		unsigned int idx;
		std::vector<std::string> playlist;
		friend class PlaylistFactory;
	};

}

#endif /* FBX_PLAYLISTBASE_H */
