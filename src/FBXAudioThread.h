/**
 * @file FBXAudioThread.h
 * @brief Audio thread definition
 * @author Christopher Han
 *
 * Audio processing thread definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_FBXAUDIOTHREAD_H
#define FBX_FBXAUDIOTHREAD_H

namespace fbx
{

	class FBXEngine;

	/**
	 * @brief FBX audio thread class
	 *
	 * Derives from wxThread
	 */
	class FBXAudioThread: public wxThread
	{
	public:
		/**
		 * @brief Entry
		 *
		 * Entry point for thread execution
		 */
		virtual void *Entry();
	protected:
		/**
		 * @brief engine
		 *
		 * Pointer to calling engine instance
		 */
		FBXEngine *engine;

		/**
		 * Friend FBXEngine so the engine can edit engine pointer
		 */
		friend class FBXEngine;
	};

}

#endif /* FBX_FBXAUDIOTHREAD_H */
