/**
 * @file PlaylistBase.cpp
 * @brief Base Playlist implementation
 * @author Christopher Han
 *
 * Base playlist data class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#include "PlaylistBase.h"
#include "../FBXUtil.h"

/**
 * Constructor
 * Typed playlists should parse/load playlist files here
 */
fbx::playlist::PlaylistBase::PlaylistBase(const std::string &fname):
	idx(0)
{
	filename = fname;
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
		idx = FBXUtil::Rand(0, playlist.size() - 1);
	} else {
		if (idx == 0)
			return false;
		idx--;
	}
	return true;
}

/**
 * Attempts to advance the playlist to the next song
 */
bool fbx::playlist::PlaylistBase::Next(bool random)
{
	if (random) {
		idx = FBXUtil::Rand(0, playlist.size() - 1);
	} else {
		if (idx >= (playlist.size() - 1))
			return false;
		idx++;
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
	return true;
}
