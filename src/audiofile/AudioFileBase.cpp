/*
 * AudioFileBase.cpp
 * Base AudioFile implementation
 * Copyright (C) 2006 Christopher Han
 */
#include "AudioFileBase.h"

fbx::AudioFileBase::AudioFileBase(const std::string& fname)
{
	filename = fname;
}

fbx::AudioFileBase::~AudioFileBase()
{
}

std::string fbx::AudioFileBase::Filename() const
{
	return filename;
}

bool fbx::AudioFileBase::Opened() const
{
	return opened;
}

std::string fbx::AudioFileBase::MetadataString()
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
