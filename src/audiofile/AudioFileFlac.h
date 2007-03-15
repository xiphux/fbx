/*
 * AudioFileFlac.h
 * FLAC AudioFile definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOFILEFLAC_H
#define FBX_AUDIOFILEFLAC_H

#include "AudioFileBase.h"

namespace fbx
{

	class AudioFileFlac: public AudioFileBase
	{
	public:
		AudioFileFlac(const std::string& fname);
		virtual ~AudioFileFlac();
		virtual int Seek(double pos);
		virtual long Read(char *buf, long len);
		virtual double Size();
		virtual double Current();
		virtual bool Eof();
		virtual std::string InfoString();
		virtual std::string Metadata(const unsigned int field);
	protected:
		FILE *fp;
		bool opened;
		FLAC__SeekableStreamDecoder *decoder;
	};

}

#endif /* FBX_AUDIOFILEFLAC_H */
