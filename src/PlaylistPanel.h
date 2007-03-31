/**
 * @file PlaylistPanel.h
 * @brief Playlist panel definition
 * @author Christopher Han
 *
 * Playlist subpanel definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_PLAYLISTPANEL_H
#define FBX_PLAYLISTPANEL_H

class wxListBox;

namespace fbx
{

	/**
	 * @brief Playlist subpanel class
	 *
	 * Derives from wxPanel
	 */
	class PlaylistPanel: public wxPanel
	{
	public:
		/**
		 * @brief Constructor
		 * @param parent pointer to parent window
		 * @param id window ID to use
		 * @param pls playlist to load
		 */
		PlaylistPanel(wxWindow *parent, wxWindowID id, const std::string& pls);

		/**
		 * @brief Load playlist
		 * @param pls playlist to load
		 * @return whether playlist successfully loaded
		 *
		 * Load a given playlist into the listbox/memory
		 */
		bool LoadPlaylist(const std::string& pls);

		/**
		 * @brief Populate playlist
		 * @return whether listbox populated
		 *
		 * Populates the listbox control with the songs from the playlist
		 */
		bool PopulatePlaylist();

		/**
		 * @brief Set active
		 * @param idx index of song to set active
		 * @param makevisible whether to move listbox to show active item
		 * @return whether active song was successfully set
		 *
		 * Sets a given song index active (in playlist and in listbox)
		 */
		bool SetActive(int idx, bool makevisible = false);

		/**
		 * @brief Next
		 * @param random whether to advance randomly
		 * @return whether playlist advance was successful
		 *
		 * Attempts to advance the playlist to the next song
		 */
		bool Next(bool random = false);

		/**
		 * @brief Prev
		 * @param random whether to advance randomly
		 * @return whether playlist advance was successful
		 *
		 * Attempts to advance the playlist to the previous song
		 */
		bool Prev(bool random = false);

		/**
		 * @brief Current
		 * @return current song path
		 *
		 * Fetches the current playlist position song file
		 */
		std::string Current();

		/**
		 * @brief Size
		 * @return size of the playlist
		 *
		 * Returns number of songs in the playlist
		 */
		unsigned int Size();

		/**
		 * @brief Add
		 * @param file new file to add
		 * @param newitem whether to add this item to the playlist in memory (in addition to the listbox)
		 * @return whether song was added successfully
		 *
		 * Adds the given song to the listbox control, and optionally, to the playlist in memory
		 */
		bool Add(const std::string& file, bool newitem = true);

		/**
		 * @brief Save
		 * @return whether save operation was successful
		 *
		 * Calls the playlist to write changes to disk
		 */
		bool Save();

		/**
		 * @brief Selected Index
		 * @return selected index
		 *
		 * Returns the currently selected listbox item's index
		 */
		unsigned int SelectedIdx();

		/**
		 * @brief Current Index
		 * @return current index
		 *
		 * Returns the current playlist song's index
		 */
		unsigned int CurrentIdx();

		/**
		 * @brief Remove
		 * @param idx index of item to remove
		 * @return whether remove was successful
		 *
		 * Attempts to remove the song at the given index from the listbox and playlist memory
		 */
		bool Remove(const unsigned int idx);

		/**
		 * @brief Get Filename
		 * @return filename of current playlist
		 *
 		 * Returns the filename of the current playlist
		 */
		std::string GetFilename();

		/**
		 * @brief Saved
		 * @return whether playlist is saved
		 *
		 * Tests whether playlist changes have been saved
		 */
		bool Saved();

	protected:
		/**
		 * @brief playlist
		 *
		 * Pointer to the current playlist
		 */
		playlist::PlaylistBase *playlist;

		/**
		 * @brief listbox
		 *
		 * Playlist listbox control
		 */
		wxListBox *listbox;
	};

}

#endif /* FBX_PLAYLISTPANEL_H */
