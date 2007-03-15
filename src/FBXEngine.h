/*
 * FBXEngine.h
 * FBX engine definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXENGINE_H
#define FBX_FBXENGINE_H

#include <string>

namespace fbx
{

	class FBXAudioThread;
	class AudioBase;
	class AudioFileBase;
	class FBXEngine
	{
	public:
		FBXEngine();
		virtual ~FBXEngine();
		bool Play(const std::string& filename);
		bool Pause();
		bool Stop();
		std::string StatusString();
		unsigned int Size();
		unsigned int Current();
		bool Stopped();
	protected:
		std::string ReadableTime(double t);
		FBXAudioThread *thread;
		AudioBase *audio;
		AudioFileBase *audiofile;
		friend class FBXAudioThread;
	};

}

#endif /* FBX_FBXENGINE_H */
