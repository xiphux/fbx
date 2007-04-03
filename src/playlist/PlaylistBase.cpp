/**
 * @file PlaylistBase.cpp
 * @brief Base Playlist implementation
 * @author Christopher Han
 *
 * Base playlist data class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "PlaylistBase.h"
#include "../FBXUtil.h"

#ifdef DEBUG
#include <iostream>
#include <sstream>
#endif

/**
 * Constructor
 * Typed playlists should parse/load playlist files here
 */
fbx::playlist::PlaylistBase::PlaylistBase(const std::string &fname):
	idx(0),
	saved(true)
{
	filename = fname;
	for (int i = 0; i < PLAYLISTHISTORYSIZE; i++)
		playlisthistory[i] = -1;
}

/**
 * Destructor
 */
fbx::playlist::PlaylistBase::~PlaylistBase()
{
}

/**
 * Attempts to write playlist to disk in specific playlist's format
 * (typed playlist classes must override this)
 */
bool fbx::playlist::PlaylistBase::Write()
{
	return false;
}

/**
 * Returns the current song (full path)
 */
std::string fbx::playlist::PlaylistBase::Current()
{
	std::string item = playlist.at(idx);
	if (item.at(0) != '/')
		item = GetPath() + "/" + item;
	return item;
}

/**
 * Returns the index of the currently active song
 */
unsigned int fbx::playlist::PlaylistBase::CurrentIdx() const
{
	return idx;
}

/**
 * Attempts to advance the playlist to the previous song
 */
bool fbx::playlist::PlaylistBase::Prev(bool random)
{
	if (random) {
		idx = Random();
	} else {
		if (idx == 0)
			return false;
		idx--;
		HistoryPush(idx);
	}
	return true;
}

/**
 * Attempts to advance the playlist to the next song
 */
bool fbx::playlist::PlaylistBase::Next(bool random)
{
	if (random) {
		idx = Random();
	} else {
		if (idx >= (playlist.size() - 1))
			return false;
		idx++;
		HistoryPush(idx);
	}
	return true;
}

/**
 * Returns the number of items in the current playlist
 */
unsigned int fbx::playlist::PlaylistBase::Size()
{
	return playlist.size();
}

/**
 * Returns the filename of the current playlist
 */
std::string fbx::playlist::PlaylistBase::GetFilename() const
{
	return filename;
}

/**
 * Sets the filename of the current playlist
 */
void fbx::playlist::PlaylistBase::SetFilename(const std::string& name)
{
	filename = name;
}

/**
 * Appends a song to the playlist
 */
void fbx::playlist::PlaylistBase::Append(const std::string& f)
{
	playlist.push_back(f);
	saved = false;
}

/**
 * Returns the path of the playlist minus the filename
 * (for use in playlist types that support relative filenames in them)
 */
std::string fbx::playlist::PlaylistBase::GetPath()
{
	std::string::size_type idx = filename.find_last_of('/');
	if ((idx >= 0) && (idx != std::string::npos))
		return filename.substr(0,idx);
	return "";
}

/**
 * Forces the given song index to be currently active
 */
bool fbx::playlist::PlaylistBase::Set(const unsigned int i)
{
	if (i >= Size())
		return false;
	idx = i;
	HistoryPush(i);
	return true;
}

/**
 * Attempts to remove song at the given index from the playlist
 */
bool fbx::playlist::PlaylistBase::Remove(const unsigned int i)
{
	if (i >= Size())
		return false;
	std::vector<std::string>::iterator it = playlist.begin();
	int j = 0;
	while (j < i) {
		it++;
		j++;
	}
	if (it == playlist.end())
		return false;
	playlist.erase(it);
	saved = false;
	return true;
}

/**
 * Attempts to generate a random song index
 */
unsigned int fbx::playlist::PlaylistBase::Random()
{
	int r = FBXUtil::Rand(0, playlist.size() - 1);
	if (playlist.size() < PLAYLISTHISTORYSIZE)
		return r;
	while (HistoryFind(r))
		r = FBXUtil::Rand(0, playlist.size() - 1);
	HistoryPush(r);
#ifdef DEBUG
	std::stringstream tmp;
	for (int i = 0; i < PLAYLISTHISTORYSIZE; i++)
		tmp << playlisthistory[i] << " ";
	std::cout << "playlisthistory: " << tmp.str() << std::endl;
#endif
	return r;
}

/**
 * Test if a given number is in the playlist history
 */
bool fbx::playlist::PlaylistBase::HistoryFind(const int x)
{
	for (int i = 0; i < PLAYLISTHISTORYSIZE; i++) {
		if (playlisthistory[i] == x)
			return true;
	}
	return false;
}

/**
 * Push an item into the history
 */
void fbx::playlist::PlaylistBase::HistoryPush(const int x)
{
	for (int i = PLAYLISTHISTORYSIZE - 1; i > 0; i--)
		playlisthistory[i] = playlisthistory[i-1];
	playlisthistory[0] = x;
}

/**
 * Tests whether playlist changes have been saved
 */
bool fbx::playlist::PlaylistBase::Saved() const
{
	return saved;
}

/**
 * Moves the given index up one
 */
bool fbx::playlist::PlaylistBase::MoveUp(const unsigned int i)
{
	if ((i >= Size()) || (i == 0))
		return false;
	std::vector<std::string>::iterator it = playlist.begin();
	int j = 0;
	while (j < i) {
		it++;
		j++;
	}
	if (it == playlist.end())
		return false;
	std::string val = *it;
	playlist.erase(it);
	it = playlist.begin();
	j = 0;
	while (j < (i - 1)) {
		it++;
		j++;
	}
	playlist.insert(it,val);
	if (i == idx)
		idx--;
	saved = false;
	return true;
}

/**
 * Moves the given index down one
 */
bool fbx::playlist::PlaylistBase::MoveDown(const unsigned int i)
{
	if (i >= (Size() - 1))
		return false;
	std::vector<std::string>::iterator it = playlist.begin();
	int j = 0;
	while (j < i) {
		it++;
		j++;
	}
	if (it == playlist.end())
		return false;
	std::string val = *it;
	playlist.erase(it);
	if (i == (Size() - 1))
		playlist.push_back(val);
	else {
		it = playlist.begin();
		j = 0;
		while (j <= i) {
			it++;
			j++;
		}
		playlist.insert(it,val);
	}
	if (i == idx)
		idx++;
	saved = false;
	return true;
}
