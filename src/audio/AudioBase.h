/*
 * AudioBase.h
 * Base Audio definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOBASE_H
#define FBX_AUDIOBASE_H

#define FBX_AUDIO_NONE 0
#define FBX_AUDIO_AO 1
#define FBX_AUDIO_ALSA 2

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
