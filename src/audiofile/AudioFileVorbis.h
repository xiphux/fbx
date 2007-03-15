/*
 * AudioFileVorbis.h
 * Vorbis AudioFile definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOFILEVORBIS_H
#define FBX_AUDIOFILEVORBIS_H

#include "AudioFileBase.h"
#include "vorbis/vorbisfile.h"

namespace fbx
{

	class AudioFileVorbis: public AudioFileBase
	{
	public:
		AudioFileVorbis(const std::string& fname);
		virtual ~AudioFileVorbis();
		virtual int Seek(double pos);
		virtual long Read(char *buf, long len);
		virtual double Size();
		virtual double Current();
		virtual bool Eof();
	protected:
		FILE *fp;
		bool opened;
		OggVorbis_File file;
	};

}

#endif /* FBX_AUDIOFILEVORBIS_H */
