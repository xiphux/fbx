/*
 * FBXEngine.cpp
 * FBX engine implementation
 * Copyright (C) 2007 Christopher Han
 */

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/thread.h>
#endif

#include "FBXEngine.h"

#include <iostream>
#include <sstream>

#include "FBXUtil.h"
#include "audiofile/AudioFileFactory.h"
#include "audio/AudioFactory.h"
#include "FBXAudioThread.h"

fbx::FBXEngine::FBXEngine()
{
	audio = 0;
	audiofile = 0;
	thread = 0;
}

fbx::FBXEngine::~FBXEngine()
{
}

bool fbx::FBXEngine::Play(const std::string& filename)
{
	if (thread)
		Stop();
	if (!fbx::AudioFileFactory::IsAudioFile(filename)) {
		std::cerr << "[FBXEngine] Not a recognized audio file: " << filename << std::endl;
		return false;
	}
	audiofile = fbx::AudioFileFactory::OpenAudioFile(filename);
	if (!audiofile) {
		std::cerr << "[FBXEngine] Error instantiating audiofile: " << filename << std::endl;
		return false;
	}
	audio = fbx::AudioFactory::CreateAudio();
	if (!audio) {
		std::cerr << "[FBXEngine] Error instantiating audio" << std::endl;
		Stop();
		return false;
	}
	thread = new FBXAudioThread();;
	if (!thread) {
		std::cerr << "[FBXEngine] Error instantiating FBXAudioThread" << std::endl;
		Stop();
		return false;;
	}
	thread->engine = this;
	thread->Create();
	thread->Run();
	return true;
}

bool fbx::FBXEngine::Pause()
{
	if (!thread)
		return false;
	if (thread->IsPaused())
		thread->Resume();
	else
		thread->Pause();
	return true;
}

bool fbx::FBXEngine::Stop()
{
	if (thread)
		thread->Delete();
//	if (audio) {
//		delete audio;
//		audio = 0;
//	}
	if (audiofile) {
		delete audiofile;
		audiofile = 0;
	}
	return true;
}

std::string fbx::FBXEngine::StatusString()
{
	std::string tmp;
	if (thread && audiofile) {
		tmp += audiofile->InfoString();
		tmp += " | ";
		tmp += FBXUtil::ReadableTime(audiofile->Current());
		tmp += " / ";
		tmp += FBXUtil::ReadableTime(audiofile->Size());
	} else
		tmp = "Stopped";
	return tmp;
}

unsigned int fbx::FBXEngine::Size()
{
	if (!audiofile)
		return 0;
	return (int)(audiofile->Size());
}

unsigned int fbx::FBXEngine::Current()
{
	if (!audiofile)
		return 0;
	return (int)(audiofile->Current());
}

bool fbx::FBXEngine::Stopped()
{
	return !(thread || audiofile);
}

bool fbx::FBXEngine::Seek(double t)
{
	if (!audiofile)
		return false;
	return (audiofile->Seek(t) == 0);
}

std::string fbx::FBXEngine::Metadata()
{
	if (!audiofile)
		return "";
	return audiofile->MetadataString();
}

bool fbx::FBXEngine::Eof()
{
	if (!audiofile)
		return true;
	return audiofile->Eof();
}
