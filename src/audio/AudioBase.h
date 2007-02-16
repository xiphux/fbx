/*
 * AudioBase.h
 * Base Audio definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOBASE_H
#define FBX_AUDIOBASE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define FBX_AUDIO_NONE 0
#ifdef HAVE_AO
#define FBX_AUDIO_AO 1
#endif
#ifdef HAVE_ALSA
#define FBX_AUDIO_ALSA 2
#endif

namespace fbx
{

	class AudioBase
	{
	public:
		virtual ~AudioBase() {};
		virtual bool Opened() = 0;
		virtual long Write(char *buf, long len) = 0;
	};

}

#endif /* FBX_AUDIOBASE_H */
