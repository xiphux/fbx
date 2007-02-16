/*
 * AudioFactory.cpp
 * Audio Factory implementation
 * Copyright (C) 2007 Christopher Han
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

fbx::AudioBase* fbx::AudioFactory::CreateAudio(const unsigned int type)
{
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
