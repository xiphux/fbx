/**
 * @file AudioFactory.cpp
 * @brief Audio Factory implementation
 *
 * Audio output driver factory class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "AudioFactory.h"
#ifdef HAVE_ALSA
#include "AudioAlsa.h"
#endif
#ifdef HAVE_AO
#include "AudioAo.h"
#endif

/**
 * Creates an instance of the audio driver that was requested
 */
fbx::AudioBase* fbx::AudioFactory::CreateAudio(unsigned int type)
{
	if (type == FBX_AUDIO_NONE)
		type = DefaultAudio();
	switch (type) {
#ifdef HAVE_AO
		case FBX_AUDIO_AO:
			return new AudioAo();
#endif
#ifdef HAVE_ALSA
		case FBX_AUDIO_ALSA:
			return new AudioAlsa();
#endif
	}
	return 0;
}

/**
 * Returns the best audio output driver for the current platform
 */
unsigned int fbx::AudioFactory::DefaultAudio()
{
#ifdef HAVE_AO
	return FBX_AUDIO_AO;
#elif defined(HAVE_ALSA)
	return FBX_AUDIO_ALSA;
#else
	return FBX_AUDIO_NONE;
#endif
}
