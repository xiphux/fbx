/*
 * AudioAo.cpp
 * Libao Audio implementation
 * Copyright (C) 2007 Christopher Han
 */

#include <iostream>
#include "AudioAo.h"

fbx::AudioAo::AudioAo()
{
	opened = false;
	ao_sample_format format;
	ao_initialize();
	int driver = ao_default_driver_id();
	format.bits = 16;
	format.channels = 2;
	format.rate = 44100;
	format.byte_format = AO_FMT_LITTLE;
	device = ao_open_live(driver, &format, NULL);
	if (!device) {
		std::cerr << "[AudioAo] Error opening device" << std::endl;
		return;
	}
	opened = true;
}

fbx::AudioAo::~AudioAo()
{
	if (device)
		ao_close(device);
	ao_shutdown();
}

long fbx::AudioAo::Write(char *buf, long len)
{
	if (!opened)
		return -1;
	return ao_play(device, buf, len);
}
