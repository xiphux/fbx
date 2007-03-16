/**
 * @file PlaylistFactory.h
 * @brief Playlist Factory definition
 * @author Christopher Han
 *
 * Playlist Factory and utility class definition
 * Copyright (C) 2007 Christopher Han
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_PLAYLISTFACTORY_H
#define FBX_PLAYLISTFACTORY_H

#include "PlaylistBase.h"

namespace fbx
{

	/**
	 * @brief Playlist factory class
	 */
	class PlaylistFactory
	{
	public:
		/**
		 * @brief Is Playlist
		 * @param filename playlist to test
		 * @return whether given file is a playlist
		 *
		 * Tests whether a given playlist filename is a recognized playlist format
		 */
		static bool IsPlaylist(const std::string& filename);

		/**
		 * @brief Playlist Type
		 * @param filename playlist to test
		 * @return type of playlist, or type NONE if unrecognized
		 *
		 * Attempts to determine the format of the given playlist
		 */
		static unsigned int PlaylistType(const std::string& filename);

		/**
		 * @brief Open Playlist
		 * @param filename playlist to open
		 * @return instance of playlist appropriate for playlist type
		 *
		 * Attempts to open a given playlist, and returns a typed playlist instance
		 * appropriate for the given playlist
		 */
		static PlaylistBase* OpenPlaylist(const std::string& filename);

		/**
		 * @brief Change Playlist Type
		 * @param orig original playlist
		 * @param fname new filename to use
		 * @return new playlist
		 *
		 * Attempts to transform an original playlist of one type into a new type based on
		 * the given filename for it
		 * (Usually used to transform untyped in-memory playlists into a typed format when
		 * saving it to a specific file)
		 */
		static PlaylistBase* ChangePlaylistType(PlaylistBase* orig, std::string fname);
	};

}

#endif /* FBX_PLAYLISTFACTORY_H */
