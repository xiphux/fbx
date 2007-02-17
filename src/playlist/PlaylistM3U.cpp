/*
 * PlaylistM3U.cpp
 * M3U Playlist implementation
 * Copyright (C) 2007 Christopher Han
 */
#include "PlaylistM3U.h"
#include <iostream>

fbx::PlaylistM3U::PlaylistM3U(const std::string& fname):
	PlaylistBase(fname)
{
	std::ifstream reader(fname.c_str());
	if (reader.good()) {
		std::string read;
		while (getline(reader,read)) {
			if (read.at(0) != '#')
				playlist.push_back(read);
		}
		reader.close();
	}
	file.open(fname.c_str());
	if (!file)
		std::cerr << "[PlaylistM3U] Could not open M3U file: " << fname << std::endl;
}

fbx::PlaylistM3U::~PlaylistM3U()
{
	file.close();
}

bool fbx::PlaylistM3U::Write()
{
	if (!file)
		return false;
	file.close();
	file.open(filename.c_str(),std::ios::out|std::ios::trunc);
	for (std::vector<std::string>::iterator iter = playlist.begin(); iter != playlist.end(); iter++)
		file << (*iter) << std::endl;
	file.flush();
}
