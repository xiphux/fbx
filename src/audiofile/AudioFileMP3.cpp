/**
 * @file AudioFileMP3.cpp
 * @brief MP3 AudioFile implementation
 * @author Christopher Han
 *
 * MP3 audiofile class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#include "AudioFileMP3.h"

/**
 * Constructor
 * Opens file
 */
fbx::audiofile::AudioFileMP3::AudioFileMP3(const std::string& fname):
	AudioFileBase(fname)
{
}

/**
 * Destructor
 * Closes file
 */
fbx::audiofile::AudioFileMP3::~AudioFileMP3()
{
}

/**
 * Attempts to seek to the given position
 */
int fbx::audiofile::AudioFileMP3::Seek(double pos)
{
}

/**
 * Attempts to read audio data from MP3 into buffer
 */
long fbx::audiofile::AudioFileMP3::Read(char *buf, long len)
{
}

/**
 * Returns the size of the loaded MP3 file
 */
double fbx::audiofile::AudioFileMP3::Size()
{
}

/**
 * Returns the current position of the playing MP3
 */
double fbx::audiofile::AudioFileMP3::Current()
{
}

/**
 * Tests whether the MP3 file has reached the EOF
 */
bool fbx::audiofile::AudioFileMP3::Eof()
{
}

/**
 * Returns a string of info about the MP3 file
 * (format, bitrate, sampling rate, channels, etc)
 */
std::string fbx::audiofile::AudioFileMP3::InfoString()
{
}

/**
 * Fetches and returns a specific field of metadata
 */
std::string fbx::audiofile::AudioFileMP3::Metadata(const unsigned int field)
{
}
