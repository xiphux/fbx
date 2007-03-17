/**
 * @file FBXFrame.h
 * @brief FBX frame definition
 * @author Christopher Han
 *
 * Main FBX window frame definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_FBXFRAME_H
#define FBX_FBXFRAME_H

#include <map>

class wxAuiNotebook;
class wxStatusBar;
class wxToolBar;
class wxSlider;
class wxTimer;
class wxTimerEvent;
class wxChoice;
class wxAuiManager;
class wxPanel;

namespace fbx
{

	namespace engine
	{
		class FBXEngine;
	}

	/**
	 * @brief FBX frame class
	 *
	 * Derives from wxFrame
	 */
	class FBXFrame: public wxFrame
	{
	public:
		/**
		 * @brief Constructor
		 */
		FBXFrame();

		/**
		 * @brief Quit event handler
		 * @param event command event
		 *
		 * Called when quit menu option is chosen
		 */
		void OnQuit(wxCommandEvent &event);

		/**
		 * @brief About event handler
		 * @param event command event
		 *
		 * Called when about menu option is chosen
		 */
		void OnAbout(wxCommandEvent &event);

		/**
		 * @brief Stop event handler
		 * @param event command event
		 *
		 * Called when stop button or menu option is chosen
		 */
		void OnStop(wxCommandEvent &event);

		/**
		 * @brief Pause event handler
		 * @param event command event
		 *
		 * Called when pause button or menu option is chosen
		 */
		void OnPause(wxCommandEvent &event);

		/**
		 * @brief Play event handler
		 * @param event command event
		 *
		 * Called when play button or menu option is chosen
		 */
		void OnPlay(wxCommandEvent &event);

		/**
		 * @brief Previous event handler
		 * @param event command event
		 *
		 * Called when prev button or menu option is chosen
		 */
		void OnPrev(wxCommandEvent &event);

		/**
		 * @brief Next event handler
		 * @param event command event
		 *
		 * Called when next button or menu option is chosen
		 */
		void OnNext(wxCommandEvent &event);

		/**
		 * @brief Seek event handler
		 * @param event scroll event
		 *
		 * Called when seek bar position is moved
		 */
		void OnSeek(wxScrollEvent &event);

		/**
		 * @brief Open playlists
		 * @param pls comma-delimited list of playlists to open
		 *
		 * Opens a series of playlists given in a string
		 */
		void OpenPlaylists(std::string pls);

		/**
		 * @brief Add playlist page
		 * @param name name of playlist to show in tab
		 * @param file filename of playlist to open
		 *
		 * Adds a page to the tabbed playlist interface with the given
		 * name/file
		 */
		void AddPlaylistPage(std::string name, std::string file);

		/**
		 * @brief Idle event handler
		 * @param event idle event
		 *
		 * Called when GUI idles
		 */
		void OnIdle(wxIdleEvent &event);

		/**
		 * @brief Playlist choice event handler
		 * @param event command event
		 *
		 * Called when double-clicking an entry in the playlist
		 */
		void OnPlaylistChoice(wxCommandEvent &event);

		/**
		 * @brief Order event handler
		 * @param event command event
		 *
		 * Called when changing the order setting in the toolbar
		 */
		void OnOrder(wxCommandEvent &event);

		/**
		 * @brief Timer event handler
		 * @param event timer event
		 *
		 * Called when update timer fires
		 */
		void OnTimer(wxTimerEvent &event);

		/**
		 * @brief Add file event handler
		 * @param event command event
		 *
		 * Called when Add Files menu option is chosen
		 */
		void OnAddFiles(wxCommandEvent& event);

		/**
		 * @brief Remove file event handler
		 * @param event command event
		 *
		 * Called when Remove file menu option is chosen
		 */
		void OnRemFile(wxCommandEvent& event);

		/**
		 * @brief Save playlist event handler
		 * @param event command event
		 *
		 * Called when Save playlist menu option is chosen
		 */
		void OnSavePlaylist(wxCommandEvent& event);

		/**
		 * @brief Update status
		 *
		 * Updates status bar information
		 */
		void UpdateStatus();

		/**
		 * @brief Reset slider
		 *
		 * Resets seek bar position and disables it (when stopping playback)
		 */
		void ResetSlider();

		/**
		 * @brief Play
		 * @param file filename to play
		 * @return whether playback successfully initiated
		 *
		 * Forwards play command to running audio engine
		 */
		bool Play(const std::string& file);

		/**
		 * @brief Try Advance
		 * @return whether playlist successfully advanced
		 *
		 * Attempts to advance playlist to next song
		 */
		bool TryAdvance();

	protected:
		/**
		 * @brief engine
		 *
		 * Pointer to audio engine instance
		 */
		engine::FBXEngine *engine;

		/**
		 * Friend FBX so app class can set engine pointer
		 */
		friend class FBX;

	private:
		DECLARE_EVENT_TABLE()

		/**
		 * @brief statusbar
		 *
		 * Statusbar instance
		 */
		wxStatusBar *statusbar;

		/**
		 * @brief playlists
		 *
		 * Map of open playlists
		 */
		std::map<std::string, std::string> playlists;

		/**
		 * @brief notebook
		 *
		 * Notebook (tabbed window) interface
		 */
		wxAuiNotebook *notebook;

		/**
		 * @brief playbacktoolbar
		 *
		 * Playback controls toolbar
		 */
		wxToolBar *playbacktoolbar;

		/**
		 * @brief ordertoolbar
		 *
		 * Order setting toolbar
		 */
		wxToolBar *ordertoolbar;

		/**
		 * @brief progresstoolbar
		 *
		 * Progress slider toolbar
		 */
		wxToolBar *progresstoolbar;

		/**
		 * @brief vistoolbar
		 *
		 * Visualization toolbar
		 */
		wxToolBar *vistoolbar;

		/**
		 * @brief progress
		 *
		 * Progress slider
		 */
		wxSlider *progress;

		/**
		 * @brief order
		 *
		 * Playback order choice
		 */
		wxChoice *order;

		/**
		 * @brief timer
		 *
		 * Update timer
		 */
		wxTimer *timer;

		/**
		 * @brief playlist index
		 *
		 * Count of open playlists
		 */
		unsigned int plidx;

		/**
		 * @brief manager
		 *
		 * Dockable toolbar manager
		 */
		wxAuiManager *manager;

		/**
		 * @brief toolbarpanel
		 *
		 * Panel containing all dockable toolbars
		 */
		wxPanel *toolbarpanel;
	};

	/**
	 * @brief frame events
	 *
	 * Enum of possible events in the frame
	 */
	enum {
		/**
		 * @brief Quit event
		 */
		FBX_frame_quit = 1,

		/**
		 * @brief About event
		 */
		FBX_frame_about,

		/**
		 * @brief Stop event
		 */
		FBX_frame_stop,

		/**
		 * @brief Pause event
		 */
		FBX_frame_pause,

		/**
		 * @brief Play event
		 */
		FBX_frame_play,

		/**
		 * @brief Prev event
		 */
		FBX_frame_prev,

		/**
		 * @brief Next event
		 */
		FBX_frame_next,

		/**
		 * @brief Progress slider event
		 */
		FBX_frame_progress,

		/**
		 * @brief Order change event
		 */
		FBX_frame_order,

		/**
		 * @brief Update timer event
		 */
		FBX_frame_timer,

		/**
		 * @brief Add files event
		 */
		FBX_frame_addfiles,

		/**
		 * @brief remove file event
		 */
		FBX_frame_remfile,

		/**
		 * @brief save playlist event
		 */
		FBX_frame_saveplaylist,

		/**
		 * @brief playlist event
		 */
		FBX_frame_playlist,
	};

}

#endif /* FBX_FBXFRAME_H */
