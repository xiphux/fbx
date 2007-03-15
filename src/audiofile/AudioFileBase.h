/*
 * AudioFileBase.h
 * Base AudioFile definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOFILEBASE_H
#define FBX_AUDIOFILEBASE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#define FBX_AUDIOFILE_NONE 0

#ifdef HAVE_VORBIS
#define FBX_AUDIOFILE_VORBIS 1
#endif

#define FBX_METADATA_NONE 0
#define FBX_METADATA_ARTIST 1
#define FBX_METADATA_ALBUM 2
#define FBX_METADATA_TRACK 3
#define FBX_METADATA_TITLE 4

namespace fbx
{

	class AudioFileBase
	{
	public:
		AudioFileBase(const std::string& fname);
		virtual ~AudioFileBase();
		virtual bool Opened() const;
		virtual int Seek(double pos) = 0;
		virtual long Read(char *buf, long len) = 0;
		virtual double Size() = 0;
		virtual double Current() = 0;
		virtual bool Eof() = 0;
		virtual std::string InfoString() = 0;
		virtual std::string Metadata(const unsigned int field) = 0;
		std::string Filename() const;
	protected:
		std::string filename;
		bool opened;
	};

}

#endif /* FBX_AUDIOFILEBASE_H */
