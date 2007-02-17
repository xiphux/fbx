/*
 * FBXFrame.cpp
 * FBX frame implementation
 * Copyright (C) 2007 Christopher Han
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/listbox.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/bitmap.h>
#include <wx/panel.h>
#include <wx/aui/auibook.h>
#endif

#include <iostream>

#include "FBXFrame.h"
#include "playlist/PlaylistFactory.h"

#include "icons/stop.xpm"
#include "icons/pause.xpm"
#include "icons/play.xpm"
#include "icons/prev.xpm"
#include "icons/next.xpm"

BEGIN_EVENT_TABLE(fbx::FBXFrame, wxFrame)
	EVT_MENU(FBX_frame_quit, fbx::FBXFrame::OnQuit)
	EVT_MENU(FBX_frame_about, fbx::FBXFrame::OnAbout)
	EVT_MENU(FBX_frame_stop, fbx::FBXFrame::OnStop)
	EVT_MENU(FBX_frame_pause, fbx::FBXFrame::OnPause)
	EVT_MENU(FBX_frame_play, fbx::FBXFrame::OnPlay)
	EVT_MENU(FBX_frame_prev, fbx::FBXFrame::OnPrev)
	EVT_MENU(FBX_frame_next, fbx::FBXFrame::OnNext)
END_EVENT_TABLE()

fbx::FBXFrame::FBXFrame():
	wxFrame((wxFrame*)NULL, -1, wxEmptyString, wxDefaultPosition, wxSize(400,300))
{
	wxString ttl = wxT(PACKAGE_STRING);
	SetTitle(ttl);

	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *filemenu = new wxMenu;
	filemenu->Append(FBX_frame_quit, wxT("E&xit"));
	menubar->Append(filemenu, wxT("&File"));
	wxMenu *playmenu = new wxMenu;
	playmenu->Append(FBX_frame_stop, wxT("&Stop"));
	playmenu->Append(FBX_frame_pause, wxT("P&ause"));
	playmenu->Append(FBX_frame_play, wxT("P&lay"));
	playmenu->Append(FBX_frame_prev, wxT("P&rev"));
	playmenu->Append(FBX_frame_next, wxT("&Next"));
	menubar->Append(playmenu, wxT("&Playback"));
	wxMenu *helpmenu = new wxMenu;
	helpmenu->Append(FBX_frame_about, wxT("&About"));
	menubar->Append(helpmenu, wxT("&Help"));
	SetMenuBar(menubar);

	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	playbacktoolbar = CreateToolBar();
	wxBitmap stopbitmap(stop_xpm);
	playbacktoolbar->AddTool(FBX_frame_stop, wxT("Stop"), stopbitmap, wxT("Stop"));
	wxBitmap pausebitmap(pause_xpm);
	playbacktoolbar->AddTool(FBX_frame_pause, wxT("Pause"), pausebitmap, wxT("Pause"));
	wxBitmap playbitmap(play_xpm);
	playbacktoolbar->AddTool(FBX_frame_play, wxT("Play"), playbitmap, wxT("Play"));
	wxBitmap prevbitmap(prev_xpm);
	playbacktoolbar->AddTool(FBX_frame_prev, wxT("Previous"), prevbitmap, wxT("Previous"));
	wxBitmap nextbitmap(next_xpm);
	playbacktoolbar->AddTool(FBX_frame_next, wxT("Next"), nextbitmap, wxT("Next"));
	playbacktoolbar->Realize();

	notebook = new wxAuiNotebook(this);
	topsizer->Add(notebook, 1, wxEXPAND|wxALL);

	statusbar = CreateStatusBar();

	SetSizer(topsizer);
}

void fbx::FBXFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void fbx::FBXFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString about = wxT(PACKAGE_STRING);
	about += wxT("\nCopyright (C) 2007 Christopher Han");
	wxMessageBox(about, wxT("About FBX"), wxOK|wxICON_INFORMATION);
}

void fbx::FBXFrame::OpenPlaylists(std::string pls)
{
	std::string::size_type lastpos = pls.find_first_not_of(",",0);
	std::string::size_type pos = pls.find_first_of(",",lastpos);
	while ((pos != std::string::npos) || (lastpos != std::string::npos)) {
		std::string pl = pls.substr(lastpos, pos - lastpos);
		if (PlaylistFactory::IsPlaylist(pl)) {
			std::string name = pls.substr(0,pls.find_last_of('.'));
			std::string::size_type tmp = name.find_last_of('/');
			if (tmp != std::string::npos)
				name = name.substr(tmp + 1);
			playlists[name] = pls;
		}
		lastpos = pls.find_first_not_of(",",pos);
		pos = pls.find_first_of(",",lastpos);
	}
	if (playlists.size() < 1)
		playlists["Default"] = "";
	for (std::map<std::string,std::string>::iterator iter = playlists.begin(); iter != playlists.end(); iter++)
		AddPlaylistPage(iter->first, iter->second);
}

void fbx::FBXFrame::AddPlaylistPage(std::string name, std::string file)
{
	wxString n(name.c_str(), *wxConvCurrent);
	notebook->AddPage((wxWindow*)(new wxPanel(notebook)), n);
}

void fbx::FBXFrame::OnStop(wxCommandEvent& WXUNUSED(event))
{
	std::cout << "FBXFrame::OnStop" << std::endl;
}

void fbx::FBXFrame::OnPause(wxCommandEvent& WXUNUSED(event))
{
	std::cout << "FBXFrame::OnPause" << std::endl;
}

void fbx::FBXFrame::OnPlay(wxCommandEvent& WXUNUSED(event))
{
	std::cout << "FBXFrame::OnPlay" << std::endl;
}

void fbx::FBXFrame::OnPrev(wxCommandEvent& WXUNUSED(event))
{
	std::cout << "FBXFrame::OnPrev" << std::endl;
}

void fbx::FBXFrame::OnNext(wxCommandEvent& WXUNUSED(event))
{
	std::cout << "FBXFrame::OnNext" << std::endl;
}
