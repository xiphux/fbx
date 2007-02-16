/*
 * AudioAlsa.cpp
 * Alsa Audio implementation
 * Copyright (C) 2007 Christopher Han
 */
#include <iostream>
#include "AudioAlsa.h"

fbx::AudioAlsa::AudioAlsa():
	opened(false)
{
	snd_pcm_hw_params_t *params;
	int err;
	if ((err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_open default: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params_malloc(&params)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_malloc: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params_any(handle, params)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_any: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_set_access: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_set_format: " << snd_strerror(err) << std::endl;
		return;
	}
	unsigned int rate = 44100;
	if ((err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_set_rate_near: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params_set_channels(handle, params, 2)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params_set_channels: " << snd_strerror(err) << std::endl;
		return;
	}
	if ((err = snd_pcm_hw_params(handle, params)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_hw_params: " << snd_strerror(err) << std::endl;
		return;
	}
	snd_pcm_hw_params_free(params);
	if ((err = snd_pcm_prepare(handle)) < 0) {
		std::cerr << "[AudioAlsa] snd_pcm_prepare: " << snd_strerror(err) << std::endl;
		return;
	}
	opened = true;
}

fbx::AudioAlsa::~AudioAlsa()
{
	snd_pcm_close(handle);
}

bool fbx::AudioAlsa::Opened()
{
	return opened;
}

long fbx::AudioAlsa::Write(char *buf, long len)
{
	if (!opened)
		return -1;
	return snd_pcm_writei(handle, buf, len);
}

