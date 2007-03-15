/*
 * FBXAudioThread.cpp
 * Audio thread implementation
 * Copyright (C) 2007 Christopher Han
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

#define BUFSIZE 2048

fbx::FBXAudioThread::FBXAudioThread():
	wxThread(wxTHREAD_DETACHED)
{
}

void *fbx::FBXAudioThread::Entry()
{
	int len = 0;
	char buf[BUFSIZE];
	while (!TestDestroy() && engine && engine->audio && engine->audiofile && !engine->audiofile->Eof()) {
		len = engine->audiofile->Read(buf, BUFSIZE);
		if (len < 0)
			std::cerr << "[FBXAudioThread] Error reading audiofile" << std::endl;
		else if (!engine->audio->Write(buf, len))
			std::cerr << "[FBXAudioThread] Error writing " << len << std::endl;
	}
	//engine->Stop();
	return 0;
}
