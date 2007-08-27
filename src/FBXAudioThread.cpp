/**
 * @file FBXAudioThread.cpp
 * @brief Audio thread implementation
 * @author Christopher Han
 *
 * Audio processing thread implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/thread.h>
#endif

#include "FBXAudioThread.h"

#include <iostream>

#include "RingBuffer.h"
#include "audio/AudioBase.h"
#include "audiofile/AudioFileBase.h"
#include "FBXEngine.h"

/**
 * @brief READFACTOR
 *
 * Bitshift multiplier factor for disk read vs audio write
 */
#define READFACTOR 2

/**
 * @brief CACHETHRESHOLD
 *
 * Bitshift multiplier of minimum audio buffers to cache
 */
#define CACHETHRESHOLD 1

/**
 * Entry point for thread execution
 */
void *fbx::engine::FBXAudioThread::Entry()
{
	if (!engine)
		return 0;
	int len = 0;
	int bufsize = engine->audiobufsize << READFACTOR;
	char buf[bufsize];
	char buf2[engine->audiobufsize];
#ifdef DEBUG
	std::cout << "AudioThread using readsize " << bufsize << " writesize " << engine->audiobufsize << std::endl;
#endif
	while (!TestDestroy() && engine->audio && engine->audiofile) {
//		engine->mutex.Lock();
		if (engine->mutex.TryLock() == wxMUTEX_NO_ERROR)
		{
			if (engine->audiofile->Eof() && engine->buffer->Empty()) {
				engine->mutex.Unlock();
				break;
			}
			if ((!engine->audiofile->Eof()) && (engine->buffer->Len() < (engine->audiobufsize << CACHETHRESHOLD))) {
				len = engine->audiofile->Read(buf, bufsize);
				if (len < 0)
					std::cerr << "[FBXAudioThread] Error reading audiofile" << std::endl;
				else if (len > 0) {
					unsigned int len2 = engine->buffer->Write(buf,len);
//					std::cout << "Audiothread read " << len << " buffered " << len2 << std::endl;
					if (len2 < len)
						std::cerr << "[FBXAudioThread] Buffer lost " << (len - len2) << std::endl;
				}
			}
			len = engine->buffer->Read(buf2,engine->audiobufsize);
//			std::cout << "Audiothread unbuffered " << len << std::endl;
			if (len > 0) {
				if (!engine->audio->Write(buf2,len))
					std::cerr << "[FBXAudioThread] Error writing " << len << std::endl;
			}
			engine->mutex.Unlock();
		}
	}
	//engine->Stop();
	return 0;
}
