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

#include "audio/AudioBase.h"
#include "audiofile/AudioFileBase.h"
#include "config/ConfigFactory.h"
#include "FBXEngine.h"

/**
 * @brief BUFSIZE
 *
 * Defines the internal audio buffer size
 */
#define BUFSIZE 4

/**
 * Entry point for thread execution
 */
void *fbx::engine::FBXAudioThread::Entry()
{
	if (!engine)
		return 0;
	int len = 0;
	int bufsize = config::ConfigFactory::GetConfig().GetInt("buffer",BUFSIZE);
	char buf[bufsize];
#ifdef DEBUG
	std::cout << "AudioThread using bufsize: " << bufsize << std::endl;
#endif
	while (!TestDestroy() && engine->audio && engine->audiofile) {
//		engine->mutex.Lock();
		if (engine->mutex.TryLock() == wxMUTEX_NO_ERROR)
		{
			if (engine->audiofile->Eof()) {
				engine->mutex.Unlock();
				break;
			}
			len = 0;
			len = engine->audiofile->Read(buf, bufsize);
			if (len < 0)
				std::cerr << "[FBXAudioThread] Error reading audiofile" << std::endl;
			else if (len > 0) {
				if (!engine->audio->Write(buf,len))
					std::cerr << "[FBXAudioThread] Error writing " << len << std::endl;
			}
			engine->mutex.Unlock();
		}
	}
	//engine->Stop();
	return 0;
}
