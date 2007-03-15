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

#include "audiofile/AudioFileFactory.h"
#include "playlist/PlaylistFactory.h"
#include "PlaylistPanel.h"

fbx::PlaylistPanel::PlaylistPanel(wxWindow *parent, wxWindowID id, const std::string& pls):
	wxPanel(parent,id)
{
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	listbox = new wxListBox(this,id);
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
	int idx = 0;
	while (idx < playlist->Size()) {
		std::string file = playlist->Current();
		std::string meta;
		AudioFileBase *tmp = AudioFileFactory::OpenAudioFile(file);
		if (tmp)
			meta = tmp->MetadataString();
		if (meta.length() > 3) {
			wxString m(meta.c_str(), *wxConvCurrent);
			listbox->Append(m,(void*)(file.c_str()));
		} else {
			wxString i(file.c_str(), *wxConvCurrent);
			listbox->Append(i,(void*)(file.c_str()));
		}
		playlist->Next();
		idx++;
	}
	playlist->Set(0);
}

bool fbx::PlaylistPanel::SetActive(int idx)
{
	playlist->Set(idx);
	listbox->SetSelection(idx);
}

bool fbx::PlaylistPanel::Next()
{
	bool ret = playlist->Next();
	if (ret)
		listbox->SetSelection(playlist->CurrentIdx());
	return ret;
}

bool fbx::PlaylistPanel::Prev()
{
	bool ret = playlist->Prev();
	if (ret)
		listbox->SetSelection(playlist->CurrentIdx());
	return ret;
}

std::string fbx::PlaylistPanel::Current()
{
	listbox->SetSelection(playlist->CurrentIdx());
	return playlist->Current();
}
