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

	namespace audio
	{

		class AudioAlsa: public AudioBase
		{
		public:
			AudioAlsa();
			virtual ~AudioAlsa();
			virtual long Write(char *buf, long len);
		protected:
			snd_pcm_t *handle;
		};

	}

}

#endif /* FBX_AUDIOALSA_H */
