/*
 * PlaylistPanel.cpp
 * Playlist panel implementation
 * Copyright (C) 2007 Christopher Han
 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#endif

#include <iostream>

#include "playlist/PlaylistFactory.h"
#include "PlaylistPanel.h"

fbx::PlaylistPanel::PlaylistPanel(wxWindow *parent, wxWindowID id, const std::string& pls):
	wxPanel(parent,id)
{
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	listbox = new wxListBox(this,-1);
	topsizer->Add(listbox,1,wxEXPAND|wxALL);

	SetSizer(topsizer);

	if (pls.length() > 0)
		LoadPlaylist(pls);
	else
		playlist = new PlaylistBase("");
}

bool fbx::PlaylistPanel::LoadPlaylist(const std::string& pls)
{
	std::cout << "PlaylistPanel::LoadPlaylist:" << pls << std::endl;
	PlaylistBase *tmp = PlaylistFactory::OpenPlaylist(pls);
	if (tmp)
		playlist = tmp;
	PopulatePlaylist();
}

bool fbx::PlaylistPanel::PopulatePlaylist()
{
	std::cout << "PlaylistPanel::PopulatePlaylist" << std::endl;
	listbox->Clear();
	for (std::vector<std::string>::iterator it = playlist->playlist.begin(); it != playlist->playlist.end(); it++) {
		std::cout << *it << std::endl;
		wxString t(it->c_str(), *wxConvCurrent);
		listbox->Append(t);
	}
}
