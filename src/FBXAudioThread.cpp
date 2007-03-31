/**
 * @file FBXAudioThread.cpp
 * @brief Audio thread implementation
 * @author Christopher Han
 *
 * Audio processing thread implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/thread.h>
#endif

#include "FBXAudioThread.h"

#include <iostream>

#include "audio/AudioBase.h"
#include "audiofile/AudioFileBase.h"
#include "FBXEngine.h"

/**
 * @brief BUFSIZE
 *
 * Defines the internal audio buffer size
 */
#define BUFSIZE 2048

/**
 * Entry point for thread execution
 */
void *fbx::engine::FBXAudioThread::Entry()
{
	int len = 0;
	char buf[BUFSIZE];
	while (!TestDestroy() && engine && engine->audio && engine->audiofile && !engine->audiofile->Eof()) {
		len = 0;
		if (engine->mutex.TryLock() == wxMUTEX_NO_ERROR) {
			len = engine->audiofile->Read(buf, BUFSIZE);
			engine->mutex.Unlock();
		}
		if (len < 0)
			std::cerr << "[FBXAudioThread] Error reading audiofile" << std::endl;
		else if (len > 0) {
			if (engine->mutex.TryLock() == wxMUTEX_NO_ERROR) {
				if (!engine->audio->Write(buf,len))
					std::cerr << "[FBXAudioThread] Error writing " << len << std::endl;
				engine->mutex.Unlock();
			}
		}
	}
	//engine->Stop();
	return 0;
}
