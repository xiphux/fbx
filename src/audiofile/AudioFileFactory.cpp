/*
 * AudioFileFactory.cpp
 * AudioFile Factory implementation
 * Copyright (C) 2006 Christopher Han
 */
#include "AudioFileFactory.h"

#ifdef HAVE_VORBIS
#include "AudioFileVorbis.h"
#endif

bool fbx::AudioFileFactory::IsAudioFile(const std::string& filename)
{
}

unsigned int fbx::AudioFileFactory::AudioFileType(const std::string& filename)
{
	unsigned int type = AudioFileTypeByMagic(filename);
	if (type > FBX_AUDIOFILE_NONE)
		return type;
	return AudioFileTypeByExtension(filename);
}

fbx::AudioFileBase* fbx::AudioFileFactory::OpenAudioFile(const std::string& filename)
{
	unsigned int type = AudioFileType(filename);
	switch (type) {
#ifdef HAVE_VORBIS
		case FBX_AUDIOFILE_VORBIS:
			return new AudioFileVorbis(filename);
			break;
#endif
	}
	return NULL;
}

unsigned int fbx::AudioFileFactory::AudioFileTypeByExtension(const std::string& filename)
{
	std::string::size_type pos = filename.find_last_of('.');
	std::string ext = filename.substr(pos+1);
#ifdef HAVE_VORBIS
	if (ext == "ogg")
		return FBX_AUDIOFILE_VORBIS;
#endif
	return FBX_AUDIOFILE_NONE;
}

unsigned int fbx::AudioFileFactory::AudioFileTypeByMagic(const std::string& filename)
{
	/* Until libmagic is used */
	return FBX_AUDIOFILE_NONE;
}
