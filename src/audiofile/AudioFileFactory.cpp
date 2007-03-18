/**
 * @file AudioFileFactory.cpp
 * @brief AudioFile Factory implementation
 * @author Christopher Han
 *
 * Audiofile factory and utility class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "AudioFileFactory.h"

#ifdef HAVE_VORBIS
#include "AudioFileVorbis.h"
#endif

#ifdef HAVE_FLAC
#include "AudioFileFlac.h"
#endif

#ifdef HAVE_MAGIC
#include <magic.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

/**
 * Tests whether given file is a recognized audio file format
 */
bool fbx::audiofile::AudioFileFactory::IsAudioFile(const std::string& filename)
{
	return (AudioFileType(filename) > FBX_AUDIOFILE_NONE);
}

/**
 * Attempts to determine the type of audio file given (or NONE if unrecognized)
 */
unsigned int fbx::audiofile::AudioFileFactory::AudioFileType(const std::string& filename)
{
	unsigned int type = FBX_AUDIOFILE_NONE;
#ifdef HAVE_MAGIC
	type = AudioFileTypeByMagic(filename);
#endif
	if (type > FBX_AUDIOFILE_NONE)
		return type;
	return AudioFileTypeByExtension(filename);
}

/**
 * Attempts to return an audiofile reader appropriate for the given filename
 */
fbx::audiofile::AudioFileBase* fbx::audiofile::AudioFileFactory::OpenAudioFile(const std::string& filename)
{
	unsigned int type = AudioFileType(filename);
	switch (type) {
#ifdef HAVE_VORBIS
		case FBX_AUDIOFILE_VORBIS:
			return new AudioFileVorbis(filename);
			break;
#endif
#ifdef HAVE_FLAC
		case FBX_AUDIOFILE_FLAC:
			return new AudioFileFlac(filename);
			break;
#endif
	}
	return NULL;
}

/**
 * Attempts to determine the type of the given audio file using its extension
 */
unsigned int fbx::audiofile::AudioFileFactory::AudioFileTypeByExtension(const std::string& filename)
{
	std::string::size_type pos = filename.find_last_of('.');
	std::string ext = filename.substr(pos+1);
#ifdef HAVE_VORBIS
	if (ext == "ogg")
		return FBX_AUDIOFILE_VORBIS;
#endif
#ifdef HAVE_FLAC
	if (ext == "flac")
		return FBX_AUDIOFILE_FLAC;
#endif
	return FBX_AUDIOFILE_NONE;
}

#ifdef HAVE_MAGIC
/**
 * Attempts to determine the type of the given audio file using libmagic
 * to test the file magic and get the mime type
 */
unsigned int fbx::audiofile::AudioFileFactory::AudioFileTypeByMagic(const std::string& filename)
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
#ifdef HAVE_VORBIS
			if (mime == "application/ogg")
				type = FBX_AUDIOFILE_VORBIS;
#endif
#ifdef HAVE_FLAC
			if (mime == "audio/x-flac")
				type = FBX_AUDIOFILE_FLAC;
#endif
		}
	}
	magic_close(cookie);
	return type;
}
#endif

/**
 * Returns a semicolon-delimited list of recognized audiofile extensions
 * (for use in open dialogs)
 */
std::string fbx::audiofile::AudioFileFactory::Extensions()
{
	std::string tmp;
#ifdef HAVE_VORBIS
	if (tmp.length() > 0)
		tmp += ";";
	tmp += "*.ogg";
#endif
#ifdef HAVE_FLAC
	if (tmp.length() > 0)
		tmp += ";";
	tmp += "*.flac";
#endif
	if (tmp.length() < 1)
		tmp = "*.*";
	return tmp;
}
