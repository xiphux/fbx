/*
 * AudioFileFactory.cpp
 * AudioFile Factory implementation
 * Copyright (C) 2006 Christopher Han
 */
#include "AudioFileFactory.h"

#ifdef HAVE_VORBIS
#include "AudioFileVorbis.h"
#endif

#ifdef HAVE_MAGIC
#include <magic.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

bool fbx::AudioFileFactory::IsAudioFile(const std::string& filename)
{
	return (AudioFileType(filename) > FBX_AUDIOFILE_NONE);
}

unsigned int fbx::AudioFileFactory::AudioFileType(const std::string& filename)
{
	unsigned int type = FBX_AUDIOFILE_NONE;
#ifdef HAVE_MAGIC
	type = AudioFileTypeByMagic(filename);
#endif
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

#ifdef HAVE_MAGIC
unsigned int fbx::AudioFileFactory::AudioFileTypeByMagic(const std::string& filename)
{
	unsigned int type = FBX_AUDIOFILE_NONE;
	magic_t cookie = magic_open(MAGIC_MIME|MAGIC_SYMLINK);
	if (!cookie)
		return type;
	if (!magic_load(cookie, NULL)) {
		const char *tmp = magic_file(cookie, filename.c_str());
		if (tmp) {
			std::string mime = tmp;
#ifdef DEBUG
			std::cout << "Mimetype: " << mime << std::endl;
#endif
			if (mime == "application/ogg")
				type = FBX_AUDIOFILE_VORBIS;
		}
	}
	magic_close(cookie);
	return type;
}
#endif

std::string fbx::AudioFileFactory::Extensions()
{
	std::string tmp;
#ifdef HAVE_VORBIS
	tmp += "*.ogg";
#endif
	if (tmp.length() < 1)
		tmp = "*.*";
	return tmp;
}
