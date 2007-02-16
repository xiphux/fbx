/*
 * AudioAlsa.h
 * Alsa Audio definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOALSA_H
#define FBX_AUDIOALSA_H

#include "AudioBase.h"
#include <asoundlib.h>

namespace fbx
{

	class AudioAlsa: public AudioBase
	{
	public:
		AudioAlsa();
		virtual ~AudioAlsa();
		virtual bool Opened();
		virtual long WriteInt(int *buf, long len);
		virtual long WriteFloat(float *buf, long len);
	protected:
		snd_pcm_t *handle;
		bool opened;
	};

}

#endif /* FBX_AUDIOALSA_H */
