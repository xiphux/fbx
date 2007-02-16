/*
 * AudioAo.h
 * Libao Audio definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOAO_H
#define FBX_AUDIOAO_H

#include "AudioBase.h"
#include <ao/ao.h>

namespace fbx
{

	class AudioAo: public AudioBase
	{
	public:
		AudioAo();
		virtual ~AudioAo();
		virtual bool Opened();
		virtual long Write(char *buf, long len);
	protected:
		ao_device *device;
		bool opened;
	};

}

#endif /* FBX_AUDIOAO_H */
