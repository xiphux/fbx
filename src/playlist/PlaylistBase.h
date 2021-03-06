/**
 * @file PlaylistBase.h
 * @brief Base Playlist definition
 * @author Christopher Han
 *
 * Base playlist data class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_PLAYLISTBASE_H
#define FBX_PLAYLISTBASE_H

#include <string>
#include <vector>

/**
 * @brief Playlist type none
 *
 * Untyped playlist
 * (only storing songs in memory, no on-disk format)
 */
#define FBX_PLAYLIST_NONE 0

/**
 * @brief Playlist type M3U
 *
 * M3U playlist
 */
#define FBX_PLAYLIST_M3U 1

/**
 * @brief Playlist type pls
 *
 * PLS playlist
 */
#define FBX_PLAYLIST_PLS 2

/**
 * @brief playlist history
 *
 * Size of playlist history to maintain
 */
#define PLAYLISTHISTORYSIZE 5

namespace fbx
{

	namespace playlist
	{

		/**
		 * @brief Base Playlist class
		 *
		 * All typed playlist must inherit from this class
		 */
		class PlaylistBase
		{
		public:
			/**
			 * @brief Constructor
			 * @param fname filename of playlist
			 *
			 * Typed playlists should parse/load playlist files here
			 */
			PlaylistBase(const std::string& fname);

			/**
			 * @brief Destructor
			 */
			virtual ~PlaylistBase();

			/**
			 * @brief Write
			 * @return whether write was successful
			 *
			 * Attempts to write playlist to disk in specific playlist's format
			 * (typed playlist classes must override this)
			 */
			virtual bool Write();

			/**
			 * @brief Current
			 * @return current song
			 *
			 * Returns the current song (full path)
			 */
			std::string Current();

			/**
			 * @brief Current index
			 * @return index of current song
			 *
			 * Returns the index of the currently active song
			 */
			unsigned int CurrentIdx() const;

			/**
			 * @brief Prev
			 * @param random whether to move randomly
			 * @return whether advance was successful
			 *
			 * Attempts to advance the playlist to the previous song
			 */
			bool Prev(bool random = false);

			/**
			 * @brief Next
			 * @param random whether to move randomly
			 * @return whether advance was successful
			 *
			 * Attempts to advance the playlist to the next song
			 */
			bool Next(bool random = false);

			/**
			 * @brief Set
			 * @param i index to set
			 * @return whether set was successful
			 *
			 * Forces the given song index to be currently active
			 */
			bool Set(const unsigned int i);

			/**
			 * @brief Size
			 * @return size of playlist
			 *
			 * Returns the number of items in the current playlist
			 */
			unsigned int Size();

			/**
			 * @brief Get Path
			 * @return path of the playlist
			 *
			 * Returns the path of the playlist minus the filename
			 * (for use in playlist types that support relative filenames in them)
			 */
			std::string GetPath();

			/**
			 * @brief Get Filename
			 * @return filename of the playlist
			 *
			 * Returns the filename of the current playlist
			 */
			std::string GetFilename() const;

			/**
			 * @brief Set Filename
			 * @param name filename to set
			 *
			 * Sets the filename of the current playlist
			 */
			void SetFilename(const std::string& name);

			/**
			 * @brief Append
			 * @param f filename to append
			 *
			 * Appends a song to the playlist
			 */
			void Append(const std::string& f);

			/**
			 * @brief Remove
			 * @param i index to remove
			 * @return whether remove was successful
			 *
			 * Attempts to remove song at the given index from the playlist
			 */
			bool Remove(const unsigned int i);

			/**
			 * @brief Saved
			 * @return whether playlist is saved
			 *
			 * Tests whether playlist changes have been saved
			 */
			bool Saved() const;

			/**
			 * @brief Move Up
			 * @param i index of track to move up
			 * @return whether move was successful
			 *
			 * Moves the given index up one
			 */
			bool MoveUp(const unsigned int i);

			/**
			 * @brief Move Down
			 * @param i index of track to move down
			 * @return whether move was successful
			 *
			 * Moves the given index down one
			 */
			bool MoveDown(const unsigned int i);

		protected:
			/**
			 * @brief Random
			 * @return random song index
			 *
			 * Attempts to generate a random song index
			 */
			unsigned int Random();

			/**
			 * @brief History Find
			 * @param x index to find
			 * @return whether item exists in history
			 *
			 * Test if a given number is in the playlist history
			 */
			bool HistoryFind(const int x);

			/**
			 * @brief History Push
			 * @param x index to push
			 *
			 * Push an item into the history
			 */
			void HistoryPush(const int x);

			/**
			 * @brief filename
			 *
			 * Current filename of the playlist
			 */
			std::string filename;

			/**
			 * @brief index
			 *
			 * Currently active song's index
			 */
			unsigned int idx;

			/**
			 * @brief playlist
			 *
			 * Vector of strings of playlist songs
			 */
			std::vector<std::string> playlist;

			/**
			 * @brief playlisthistory
			 *
			 * History of songs played
			 */
			int playlisthistory[PLAYLISTHISTORYSIZE];

			/**
			 * @brief saved
			 *
			 * Whether playlist changes have been saved
			 */
			bool saved;

			/**
			 * friend PlaylistFactory so factory can perform
			 * playlist type transforms
			 */
			friend class PlaylistFactory;

			/**
			 * friend PlaylistPanel so panel can access playlist song data
			 */
			friend class PlaylistPanel;
		};

	}

}

#endif /* FBX_PLAYLISTBASE_H */
