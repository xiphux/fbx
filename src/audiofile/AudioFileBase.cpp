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
