/*
 * AudioFactory.h
 * Audio Factory definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOFACTORY_H
#define FBX_AUDIOFACTORY_H

#include "AudioBase.h"

namespace fbx
{

	class AudioFactory
	{
	public:
		static AudioBase *CreateAudio(const unsigned int type);
	};

}

#endif /* FBX_AUDIOFACTORY_H */
