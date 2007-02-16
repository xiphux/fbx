/*
 * AudioFileVorbis.cpp
 * Vorbis AudioFile implementation
 * Copyright (C) 2007 Christopher Han
 */

#include <iostream>
#include "AudioFileVorbis.h"

fbx::AudioFileVorbis::AudioFileVorbis(const std::string& fname):
	AudioFileBase(fname),
	opened(false)
{
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

fbx::AudioFileVorbis::~AudioFileVorbis()
{
	if (opened && ov_clear(&file))
		std::cerr << "[AudioFileVorbis] Failed to clear vorbis" << std::endl;
//	if (fp && fclose(fp))
//		std::cerr << "[AudioFileVorbis] Failed to close file" << std::endl;
}

bool fbx::AudioFileVorbis::Opened()
{
	return opened;
}

int fbx::AudioFileVorbis::Seek(double pos)
{
	if (!opened)
		return -1;
	return ov_time_seek(&file, pos);
}

long fbx::AudioFileVorbis::Read(char *buf, long len)
{
	if (!opened)
		return -1;
	int section;
	return ov_read(&file, buf, len, 0, 2, 1, &section);
}

double fbx::AudioFileVorbis::Size()
{
	if (!opened)
		return -1;
	return ov_time_total(&file, -1);
}

bool fbx::AudioFileVorbis::Eof()
{
	if (!opened)
		return true;
	return (ov_time_tell(&file) >= ov_time_total(&file, -1));
}

