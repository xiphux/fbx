/*
 * AudioFactory.cpp
 * Audio Factory implementation
 * Copyright (C) 2007 Christopher Han
 */
#include "AudioFactory.h"
#include "AudioAlsa.h"
#include "AudioAo.h"

fbx::AudioBase* fbx::AudioFactory::CreateAudio(const unsigned int type)
{
	switch (type) {
		case FBX_AUDIO_AO:
			return new AudioAo();
		case FBX_AUDIO_ALSA:
			return new AudioAlsa();
	}
	return 0;
}
