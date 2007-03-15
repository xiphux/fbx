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
		std::string Filename() const;
	protected:
		std::string filename;
		bool opened;
	};

}

#endif /* FBX_AUDIOFILEBASE_H */
