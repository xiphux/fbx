/*
 * FBXFrame.h
 * FBX frame definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXFRAME_H
#define FBX_FBXFRAME_H

#include <map>

class wxAuiManager;
class wxAuiNotebook;
class wxStatusBar;

namespace fbx
{

	class FBXFrame: public wxFrame
	{
	public:
		FBXFrame();
		virtual ~FBXFrame();
		void OnQuit(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);
		void OpenPlaylists(std::string pls);
		void AddPlaylistPage(std::string name, std::string file);
	private:
		DECLARE_EVENT_TABLE()
		wxAuiManager *manager;
		wxStatusBar *statusbar;
		std::map<std::string, std::string> playlists;
		wxAuiNotebook *notebook;
	};

	enum {
		FBX_frame_quit = 1,
		FBX_frame_about,
	};

}

#endif /* FBX_FBXFRAME_H */
