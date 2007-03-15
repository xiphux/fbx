/*
 * PlaylistPanel.cpp
 * Playlist panel implementation
 * Copyright (C) 2007 Christopher Han
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#endif

#include <iostream>

#include "FBXUtil.h"
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
#ifdef DEBUG
	std::cout << "PlaylistPanel::LoadPlaylist:" << pls << std::endl;
#endif
	PlaylistBase *tmp = PlaylistFactory::OpenPlaylist(pls);
	if (tmp)
		playlist = tmp;
	PopulatePlaylist();
}

bool fbx::PlaylistPanel::PopulatePlaylist()
{
#ifdef DEBUG
	std::cout << "PlaylistPanel::PopulatePlaylist" << std::endl;
#endif
	listbox->Clear();
	int idx = 0;
	while (idx < playlist->Size()) {
		std::string file = playlist->Current();
		std::string meta;
		AudioFileBase *tmp = AudioFileFactory::OpenAudioFile(file);
		if (tmp)
			meta = tmp->MetadataString();
		if (meta.length() > 3) {
			if (tmp) {
				meta += " (";
				meta += FBXUtil::ReadableTime(tmp->Size());
				meta += ")";
			}
			wxString m(meta.c_str(), *wxConvCurrent);
			listbox->Append(m,(void*)(file.c_str()));
		} else {
			std::string fname = file;
			if (tmp) {
				fname += " (";
				fname += FBXUtil::ReadableTime(tmp->Size());
				fname += ")";
			}
			wxString i(fname.c_str(), *wxConvCurrent);
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