/**
 * @file AudioFileBase.cpp
 * @brief Base AudioFile implementation
 * @author Christopher Han
 *
 * Base abstract audiofile class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "AudioFileBase.h"

/**
 * Constructor
 */
fbx::audiofile::AudioFileBase::AudioFileBase(const std::string& fname)
{
	filename = fname;
}

/**
 * Destructor
 */
fbx::audiofile::AudioFileBase::~AudioFileBase()
{
}

/**
 * Returns the currently open filename
 */
std::string fbx::audiofile::AudioFileBase::Filename() const
{
	return filename;
}

/**
 * Tests whether audiofile is successfully opened
 */
bool fbx::audiofile::AudioFileBase::Opened() const
{
	return opened;
}

/**
 * Returns a formatted string of a number of common metadata fields
 */
std::string fbx::audiofile::AudioFileBase::MetadataString()
{
	std::string tmp;
	tmp += Metadata(FBX_METADATA_ARTIST);
	tmp += " - ";

	std::string tmp2;
	tmp2 += "[";
	std::string album = Metadata(FBX_METADATA_ALBUM);
	std::string trackno = Metadata(FBX_METADATA_TRACK);
	if (album.length() > 0) {
		tmp2 += album;
		if (trackno.length() > 0)
			tmp2 += " ";
	}
	if (trackno.length() > 0) {
		tmp2 += "#";
		tmp2 += trackno;
	}
	tmp2 += "]";
	if (tmp2.length() > 2) {
		tmp += tmp2;
		tmp += " ";
	}
	tmp += Metadata(FBX_METADATA_TITLE);
	return tmp;
}
