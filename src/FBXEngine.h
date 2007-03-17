/**
 * @file FBXEngine.h
 * @brief FBX engine definition
 * @author Christopher Han
 *
 * Audio processing engine definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_FBXENGINE_H
#define FBX_FBXENGINE_H

#include <string>

namespace fbx
{

	class FBXAudioThread;
	class AudioBase;
	class AudioFileBase;

	/**
	 * @brief FBX audio engine class
	 */
	class FBXEngine
	{
	public:
		/**
		 * @brief Constructor
		 */
		FBXEngine();

		/**
		 * @brief Destructor
		 */
		virtual ~FBXEngine();

		/**
		 * @brief Play
		 * @param filename path to file to play
		 * @return whether playback initialized successfully
		 *
		 * Tells the engine to begin processing and playback of a file
		 */
		bool Play(const std::string& filename);

		/**
		 * @brief Pause
		 * @return whether pause was successful
		 *
		 * Pauses or unpauses playback thread
		 */
		bool Pause();

		/**
		 * @brief Stop
		 * @return whether stop was successful
		 *
		 * Stops a running audiofile / audiothread if there is one
		 */
		bool Stop();

		/**
		 * @brief Seek
		 * @param t time position to seek to (in seconds)
		 * @return whether seek was successful
		 *
		 * Seeks audiofile to a specific position
		 */
		bool Seek(double t);

		/**
		 * @brief Status String
		 * @return status string
		 *
		 * Outputs the status string for the current file
		 * (file type, info, current time, total length, etc)
		 */
		std::string StatusString();

		/**
		 * @brief Metadata
		 * @return metadata string
		 *
		 * Outputs the metadata of the playing file in a
		 * formatted manner
		 */
		std::string Metadata();

		/**
		 * @brief Size
		 * @return size of file
		 * 
		 * Gives the size of the currently playing file (in seconds)
		 */
		unsigned int Size();

		/**
		 * @brief current
		 * @return current position
		 *
		 * Gives the current position of the playing audiofile (in seconds)
		 */
		unsigned int Current();

		/**
		 * @brief End of file
		 * @return whether audiofile has reached EOF
		 *
		 * Returns whether the current file has reached the end
		 * of the file (finished playback)
		 */
		bool Eof();

		/**
		 * @brief Stopped
		 * @return whether engine is stopped
		 *
		 * Returns whether the engine is currently playing a file or stopped
		 */
		bool Stopped();

		/**
		 * @brief Paused
		 * @return whether engine is paused
		 *
		 * Returns whether the engine is current playing but paused
		 */
		bool Paused();

	protected:
		/**
		 * @brief thread
		 *
		 * Pointer to current audio thread instance
		 */
		FBXAudioThread *thread;

		/**
		 * @brief audio
		 *
		 * Pointer to current audio output driver
		 */
		AudioBase *audio;

		/**
		 * @brief audiofile
		 *
		 * Pointer to currently processing audiofile
		 */
		AudioFileBase *audiofile;

		/**
		 * Friend FBXAudioThread so audiothread can access
		 * audio/audiofile data structures
		 */
		friend class FBXAudioThread;
	};

}

#endif /* FBX_FBXENGINE_H */
