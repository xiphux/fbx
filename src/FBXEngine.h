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
		bool Seek(double t);
		std::string StatusString();
		std::string Metadata();
		unsigned int Size();
		unsigned int Current();
		bool Eof();
		bool Stopped();
	protected:
		FBXAudioThread *thread;
		AudioBase *audio;
		AudioFileBase *audiofile;
		friend class FBXAudioThread;
	};

}

#endif /* FBX_FBXENGINE_H */
