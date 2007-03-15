/*
 * FBXFrame.h
 * FBX frame definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXFRAME_H
#define FBX_FBXFRAME_H

#include <map>

class wxAuiNotebook;
class wxStatusBar;
class wxToolBar;
class wxSlider;

namespace fbx
{

	class FBXEngine;
	class FBXFrame: public wxFrame
	{
	public:
		FBXFrame();
		void OnQuit(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);
		void OnStop(wxCommandEvent &event);
		void OnPause(wxCommandEvent &event);
		void OnPlay(wxCommandEvent &event);
		void OnPrev(wxCommandEvent &event);
		void OnNext(wxCommandEvent &event);
		void OpenPlaylists(std::string pls);
		void AddPlaylistPage(std::string name, std::string file);
		void OnIdle(wxIdleEvent &event);
		void ResetSlider();
		bool Play(const std::string& file);
	protected:
		FBXEngine *engine;
		friend class FBX;
	private:
		DECLARE_EVENT_TABLE()
		wxStatusBar *statusbar;
		std::map<std::string, std::string> playlists;
		wxAuiNotebook *notebook;
		wxToolBar *playbacktoolbar;
		wxToolBar *ordertoolbar;
		wxToolBar *progresstoolbar;
		wxToolBar *vistoolbar;
		wxSlider *progress;
	};

	enum {
		FBX_frame_quit = 1,
		FBX_frame_about,
		FBX_frame_stop,
		FBX_frame_pause,
		FBX_frame_play,
		FBX_frame_prev,
		FBX_frame_next,
		FBX_frame_progress,
	};

}

#endif /* FBX_FBXFRAME_H */
