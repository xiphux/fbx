/**
 * @file AudioFileVorbis.cpp
 * @brief Vorbis AudioFile implementation
 * @author Christopher Han
 *
 * Ogg Vorbis audiofile class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#include <iostream>
#include <sstream>
#include "AudioFileVorbis.h"

/**
 * Constructor
 * Opens file and initializes libvorbisfile
 */
fbx::audiofile::AudioFileVorbis::AudioFileVorbis(const std::string& fname):
	AudioFileBase(fname)
{
	opened = false;
	fp = fopen(fname.c_str(), "rb");
	if (!fp) {
		std::cerr << "[AudioFileVorbis] Error opening file: " << fname << std::endl;
		return;
	}
	if (ov_open(fp, &file, NULL, 0)) {
		std::cerr << "[AudioFileVorbis] Error opening vorbis: " << fname << std::endl;
		return;
	}
	opened = true;
}

/**
 * Destructor
 * Closes file and libvorbisfile
 */
fbx::audiofile::AudioFileVorbis::~AudioFileVorbis()
{
	if (opened && ov_clear(&file))
		std::cerr << "[AudioFileVorbis] Failed to clear vorbis" << std::endl;
//	if (fp && fclose(fp))
//		std::cerr << "[AudioFileVorbis] Failed to close file" << std::endl;
}

/**
 * Attempts to seek to the given position
 */
int fbx::audiofile::AudioFileVorbis::Seek(double pos)
{
	if (!opened)
		return -1;
	return ov_time_seek(&file, pos);
}

/**
 * Attempts to read audio data from vorbis file into buffer
 */
long fbx::audiofile::AudioFileVorbis::Read(char *buf, long len)
{
	if (!opened)
		return -1;
	int section;
	return ov_read(&file, buf, len, 0, 2, 1, &section);
}

/**
 * Returns the size of the loaded vorbis file
 */
double fbx::audiofile::AudioFileVorbis::Size()
{
	if (!opened)
		return -1;
	return ov_time_total(&file, -1);
}

/**
 * Returns the current position of the playing vorbis file
 */
double fbx::audiofile::AudioFileVorbis::Current()
{
	if (!opened)
		return -1;
	return ov_time_tell(&file);
}

/**
 * Tests whether the vorbis file has reached the EOF
 */
bool fbx::audiofile::AudioFileVorbis::Eof()
{
	if (!opened)
		return true;
	return (ov_time_tell(&file) >= ov_time_total(&file, -1));
}

/**
 * Returns a string of info about the vorbis file
 * (format, bitrate, sampling rate, channels, etc)
 */
std::string fbx::audiofile::AudioFileVorbis::InfoString()
{
	std::stringstream str;
	str << "Vorbis";
	if (opened) {
		str << " ";
		str << (int)(ov_bitrate_instant(&file) / 1024);
		//str << (int)(ov_bitrate(&file,-1) / 1024);
		str << "kbps";
		vorbis_info *tmp = ov_info(&file,-1);
		if (tmp) {
			str << " ";
			str << tmp->rate;
			str << "Hz";
			str << " ";
			if (tmp->channels == 1)
				str << "mono";
			else
				str << "stereo";
		}
	}
	return str.str();
}

/**
 * Fetches and returns a specific field of metadata
 */
std::string fbx::audiofile::AudioFileVorbis::Metadata(const unsigned int field)
{
	if (opened) {
		vorbis_comment *com = ov_comment(&file,-1);
		if (com) {
			std::string idx;
			switch (field) {
				case FBX_METADATA_TITLE:
					idx = "TITLE";
					break;
				case FBX_METADATA_TRACK:
					idx = "TRACKNUMBER";
					break;
				case FBX_METADATA_ALBUM:
					idx = "ALBUM";
					break;
				case FBX_METADATA_ARTIST:
					idx = "ARTIST";
					break;
				default:
					return "";
			}
			idx += "=";
			for (int i = 0; i < com->comments; i++) {
				std::string uc = com->user_comments[i];
				if (idx == uc.substr(0,idx.length()))
					return uc.substr(idx.length());
			}
		}
	}
	return "";
}
