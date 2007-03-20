/**
 * @file PlaylistM3U.cpp
 * @brief M3U Playlist implementation
 * @author Christopher Han
 *
 * M3U typed playlist class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "PlaylistM3U.h"
#include <iostream>

/**
 * Constructor
 * Loads and parses given M3U list
 */
fbx::playlist::PlaylistM3U::PlaylistM3U(const std::string& fname):
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
}

/**
 * Destructor
 */
fbx::playlist::PlaylistM3U::~PlaylistM3U()
{
}

/**
 * Attempts to write playlist data to disk in M3U format
 */
bool fbx::playlist::PlaylistM3U::Write()
{
	file.open(filename.c_str(),std::ios::out|std::ios::trunc);
	if (!file) {
		std::cerr << "[PlaylistM3U] Could not open M3U file: " << filename << std::endl;
		return false;
	}
	for (std::vector<std::string>::iterator iter = playlist.begin(); iter != playlist.end(); iter++) {
		if (GetPath() == iter->substr(0,GetPath().length()))
			file << iter->substr(GetPath().length()+1) << std::endl;
		else
			file << (*iter) << std::endl;
	}
	file.flush();
	file.close();
}
