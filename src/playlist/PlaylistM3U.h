/**
 * @file PlaylistM3U.h
 * @brief M3U Playlist definition
 * @author Christopher Han
 *
 * M3U typed playlist class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_PLAYLISTM3U_H
#define FBX_PLAYLISTM3U_H

#include "PlaylistBase.h"

#include <fstream>

namespace fbx
{

	namespace playlist
	{

		/**
		 * @brief M3U Playlist class
		 *
		 * Derives from PlaylistBase
		 */
		class PlaylistM3U: public PlaylistBase
		{
		public:
			/**
			 * @brief Constructor
			 * @param fname filename to load
			 *
			 * Loads and parses given M3U list
			 */
			PlaylistM3U(const std::string& fname);

			/**
			 * @brief Destructor
			 *
			 * Cleans up open file references
			 */
			virtual ~PlaylistM3U();

			/**
			 * @brief Write
			 * @return whether write was successful
			 *
			 * Attempts to write playlist data to disk in M3U format
			 */
			virtual bool Write();

		protected:
			/**
			 * @brief file
			 *
			 * Output file stream
			 */
			std::ofstream file;
		};

	}

}

#endif /* FBX_PLAYLISTM3U_H */
