/**
 * @file PlaylistPanel.cpp
 * @brief Playlist panel implementation
 * @author Christopher Han
 *
 * Playlist subpanel implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
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

#ifdef DEBUG
#include <iostream>
#endif

#include "FBXUtil.h"
#include "audiofile/AudioFileFactory.h"
#include "playlist/PlaylistFactory.h"
#include "PlaylistPanel.h"

/**
 * Constructor
 */
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
		playlist = new playlist::PlaylistBase("");
}

/**
 * Load a given playlist into the listbox/memory
 */
bool fbx::PlaylistPanel::LoadPlaylist(const std::string& pls)
{
#ifdef DEBUG
	std::cout << "PlaylistPanel::LoadPlaylist:" << pls << std::endl;
#endif
	playlist::PlaylistBase *tmp = playlist::PlaylistFactory::OpenPlaylist(pls);
	if (tmp)
		playlist = tmp;
	PopulatePlaylist();
}

/**
 * Populates the listbox control with the songs from the playlist
 */
bool fbx::PlaylistPanel::PopulatePlaylist()
{
#ifdef DEBUG
	std::cout << "PlaylistPanel::PopulatePlaylist" << std::endl;
#endif
	listbox->Clear();
	unsigned int oldidx = playlist->CurrentIdx();
	playlist->Set(0);
	int idx = 0;
	while (idx < playlist->Size()) {
		Add(playlist->Current(),false);
		playlist->Next(false);
		idx++;
	}
	playlist->Set(oldidx);
}

/**
 * Sets a given song index active (in playlist and in listbox)
 */
bool fbx::PlaylistPanel::SetActive(int idx, bool makevisible)
{
	playlist->Set(idx);
	listbox->SetSelection(idx);
	if (makevisible)
		listbox->SetFirstItem(idx);
}

/**
 * Attempts to advance the playlist to the next song
 */
bool fbx::PlaylistPanel::Next(bool random)
{
	bool ret = playlist->Next(random);
	if (ret)
		listbox->SetSelection(playlist->CurrentIdx());
	listbox->SetFirstItem(playlist->CurrentIdx());
	return ret;
}

/**
 * Attempts to advance the playlist to the previous song
 */
bool fbx::PlaylistPanel::Prev(bool random)
{
	bool ret = playlist->Prev(random);
	if (ret)
		listbox->SetSelection(playlist->CurrentIdx());
	listbox->SetFirstItem(playlist->CurrentIdx());
	return ret;
}

/**
 * Fetches the current playlist position song file
 */
std::string fbx::PlaylistPanel::Current()
{
	listbox->SetSelection(playlist->CurrentIdx());
	return playlist->Current();
}

/**
 * Returns number of songs in the playlist
 */
unsigned int fbx::PlaylistPanel::Size()
{
	return playlist->Size();
}

/**
 * Adds the given song to the listbox control, and optionally, to the playlist in memory
 */
bool fbx::PlaylistPanel::Add(const std::string& file, bool newitem)
{
	std::string meta;
	audiofile::AudioFileBase *tmp = audiofile::AudioFileFactory::OpenAudioFile(file);
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
	if (newitem)
		playlist->Append(file);
	return true;
}

/**
 * Calls the playlist to write changes to disk
 */
bool fbx::PlaylistPanel::Save()
{
	return playlist->Write();
}

/**
 * Returns the currently selected listbox item's index
 */
unsigned int fbx::PlaylistPanel::SelectedIdx()
{
	return listbox->GetSelection();
}

/**
 * Returns the current playlist song's index
 */
unsigned int fbx::PlaylistPanel::CurrentIdx()
{
	return playlist->CurrentIdx();
}

/**
 * Attempts to remove the song at the given index from the listbox and playlist memory
 */
bool fbx::PlaylistPanel::Remove(const unsigned int idx)
{
	if ((idx >= playlist->Size()) || (idx >= listbox->GetCount()))
		return false;
	playlist->Remove(idx);
	listbox->Delete(idx);
	return true;
}

/**
 * Returns the filename of the current playlist
 */
std::string fbx::PlaylistPanel::GetFilename()
{
	return playlist->GetFilename();
}

/**
 * Tests whether playlist changes have been saved
 */
bool fbx::PlaylistPanel::Saved()
{
	return playlist->Saved();
}

/**
 * Sets the filename of the playlist, transforming its type
 */
bool fbx::PlaylistPanel::SetFilename(const std::string fname)
{
	playlist::PlaylistBase *tmp = playlist::PlaylistFactory::ChangePlaylistType(playlist, fname);
	if (!tmp)
		return false;
	playlist::PlaylistBase *tmp2 = playlist;
	playlist = tmp;
	delete tmp2;
	return true;
}

/**
 * Move specified item up
 */
bool fbx::PlaylistPanel::MoveUp(const unsigned int idx)
{
	bool ret = playlist->MoveUp(idx);
	if (ret) {
		PopulatePlaylist();
		listbox->SetSelection(idx - 1);
	}
	return ret;
}

/**
 * Move specified item down
 */
bool fbx::PlaylistPanel::MoveDown(const unsigned int idx)
{
	bool ret = playlist->MoveDown(idx);
	if (ret) {
		PopulatePlaylist();
		listbox->SetSelection(idx + 1);
	}
	return ret;
}
