/*
 * PlaylistBase.cpp
 * Base Playlist implementation
 * Copyright (C) 2007 Christopher Han
 */

#include "PlaylistBase.h"
#include "../FBXUtil.h"

fbx::PlaylistBase::PlaylistBase(const std::string &fname):
	idx(0)
{
	filename = fname;
}

fbx::PlaylistBase::~PlaylistBase()
{
}

bool fbx::PlaylistBase::Write()
{
	return false;
}

std::string fbx::PlaylistBase::Current()
{
	std::string item = playlist.at(idx);
	if (item.at(0) != '/')
		item = GetPath() + "/" + item;
	return item;
}

unsigned int fbx::PlaylistBase::CurrentIdx() const
{
	return idx;
}

bool fbx::PlaylistBase::Prev(bool random)
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

bool fbx::PlaylistBase::Next(bool random)
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

unsigned int fbx::PlaylistBase::Size()
{
	return playlist.size();
}

std::string fbx::PlaylistBase::GetFilename() const
{
	return filename;
}

void fbx::PlaylistBase::SetFilename(const std::string& name)
{
	filename = name;
}

void fbx::PlaylistBase::Append(const std::string& f)
{
	playlist.push_back(f);
}

std::string fbx::PlaylistBase::GetPath()
{
	std::string::size_type idx = filename.find_last_of('/');
	if ((idx >= 0) && (idx != std::string::npos))
		return filename.substr(0,idx);
	return "";
}

bool fbx::PlaylistBase::Set(const unsigned int i)
{
	if (i >= Size())
		return false;
	idx = i;
	return true;
}

bool fbx::PlaylistBase::Remove(const unsigned int i)
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
