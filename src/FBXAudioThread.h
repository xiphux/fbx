/*
 * FBXAudioThread.h
 * Audio thread definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXAUDIOTHREAD_H
#define FBX_FBXAUDIOTHREAD_H

namespace fbx
{

	class FBXEngine;
	class FBXAudioThread: public wxThread
	{
	public:
		FBXAudioThread();
		virtual void *Entry();
	protected:
		FBXEngine *engine;
		friend class FBXEngine;
	};

}

#endif /* FBX_FBXAUDIOTHREAD_H */
