/**
 * @file FBXEngine.cpp
 * @brief FBX engine implementation
 * @author Christopher Han
 *
 * Audio processing engine implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
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

/**
 * Constructor
 */
fbx::engine::FBXEngine::FBXEngine()
{
	audio = 0;
	audiofile = 0;
	thread = 0;
}

/**
 * Destructor
 */
fbx::engine::FBXEngine::~FBXEngine()
{
	Stop();
}

/**
 * Tells the engine to begin processing and playback of a file
 */
bool fbx::engine::FBXEngine::Play(const std::string& filename)
{
	//if (thread || audiofile)
		Stop();
	if (!audiofile::AudioFileFactory::IsAudioFile(filename)) {
		std::cerr << "[FBXEngine] Not a recognized audio file: " << filename << std::endl;
		return false;
	}
	audiofile = audiofile::AudioFileFactory::OpenAudioFile(filename);
	if (!audiofile) {
		std::cerr << "[FBXEngine] Error instantiating audiofile: " << filename << std::endl;
		return false;
	}
	audio = audio::AudioFactory::CreateAudio();
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

/**
 * Pauses or unpauses playback thread
 */
bool fbx::engine::FBXEngine::Pause()
{
	if (!thread)
		return false;
	if (thread->IsPaused())
		thread->Resume();
	else
		thread->Pause();
	return true;
}

/**
 * Stops a running audiofile / audiothread if there is one
 */
bool fbx::engine::FBXEngine::Stop()
{
//	if (thread)
//		thread->Delete();
	mutex.Lock();	
	if (audiofile) {
		delete audiofile;
		audiofile = 0;
	}
	if (audio) {
		delete audio;
		audio = 0;
	}
	mutex.Unlock();
	return true;
}

/**
 * Outputs the status string for the current file
 * (file type, info, current time, total length, etc)
 */
std::string fbx::engine::FBXEngine::StatusString()
{
	std::string tmp;
	if (audiofile) {
		tmp += audiofile->InfoString();
		tmp += " | ";
		tmp += FBXUtil::ReadableTime(audiofile->Current());
		tmp += " / ";
		tmp += FBXUtil::ReadableTime(audiofile->Size());

		/*
		 * This next part should be temporary if possible
		 */
		tmp += " | ";
		std::string tmp2 = audiofile->MetadataString();
		if (tmp2.length() > 3)
			tmp += tmp2;
		else
			tmp += audiofile->Filename();

	} else
		tmp = "Stopped";
	return tmp;
}

/**
 * Gives the size of the currently playing file (in seconds)
 */
unsigned int fbx::engine::FBXEngine::Size()
{
	if (!audiofile)
		return 0;
	return (int)(audiofile->Size());
}

/**
 * Gives the current position of the playing audiofile (in seconds)
 */
unsigned int fbx::engine::FBXEngine::Current()
{
	if (!audiofile)
		return 0;
	return (int)(audiofile->Current());
}

/**
 * Returns whether the engine is currently playing a file or stopped
 */
bool fbx::engine::FBXEngine::Stopped()
{
	return !(thread && audiofile);
}

/**
 * Seeks audiofile to a specific position
 */
bool fbx::engine::FBXEngine::Seek(double t)
{
	if (!audiofile)
		return false;
	int ret;
	mutex.Lock();
	ret = audiofile->Seek(t);
	mutex.Unlock();
	return (ret == 0);
}

/**
 * Outputs the metadata of the playing file in a
 * formatted manner
 */
std::string fbx::engine::FBXEngine::Metadata()
{
	if (!audiofile)
		return "";
	return audiofile->MetadataString();
}

/**
 * Returns whether the current file has reached the end
 * of the file (finished playback)
 */
bool fbx::engine::FBXEngine::Eof()
{
	if (!audiofile)
		return true;
	return audiofile->Eof();
}

/**
 * Returns whether the engine is current playing but paused
 */
bool fbx::engine::FBXEngine::Paused()
{
	return (thread && thread->IsPaused());
}
