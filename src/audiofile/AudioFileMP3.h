/**
 * @file AudioFileMP3.h
 * @brief MP3 AudioFile definition
 * @author Christopher Han
 *
 * MP3 (libmad) audiofile class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFILEMP3_H
#define FBX_AUDIOFILEMP3_H

#include "AudioFileBase.h"

namespace fbx
{

	namespace audiofile
	{

		/**
		 * @brief MP3 audiofile class
		 *
		 * Implements AudioFileBase
		 */
		class AudioFileMP3: public AudioFileBase
		{
		public:
			/**
			 * @brief Constructor
			 * @param fname filename to open
			 *
			 * Opens file
			 */
			AudioFileMP3(const std::string& fname);

			/**
			 * @brief Destructor
			 *
			 * Closes file
			 */
			virtual ~AudioFileMP3();

			/**
			 * @brief Seek
			 * @param pos position to seek to in seconds
			 * @return whether seek was successful
			 *
			 * Attempts to seek to the given position
			 */
			virtual int Seek(double pos);

			/**
			 * @brief Read
			 * @param buf buffer to read into
			 * @param len amount of data to read
			 * @return amount of data read
			 *
			 * Attempts to read audio data from MP3 into buffer
			 */
			virtual long Read(char *buf, long len);

			/**
			 * @brief Size
			 * @return size of MP3 file
			 * 
			 * Returns the size of the loaded MP3 file
			 */
			virtual double Size();

			/**
			 * @brief Current
			 * @return current position of MP3
			 *
			 * Returns the current position of the playing MP3
			 */
			virtual double Current();

			/**
			 * @brief End of file
			 * @return whether the MP3 is at the end of file
			 *
			 * Tests whether the MP3 file has reached the EOF
			 */
			virtual bool Eof();

			/**
			 * @brief Info String
			 * @return string of info about file
			 *
			 * Returns a string of info about the MP3 file
			 * (format, bitrate, sampling rate, channels, etc)
			 */
			virtual std::string InfoString();

			/**
			 * @brief Metadata
			 * @param field metadata field to fetch
			 * @return string of metadata requested
			 *
			 * Fetches and returns a specific field of metadata
			 */
			virtual std::string Metadata(const unsigned int field);

		};

	}

}

#endif /* FBX_AUDIOFILEMP3_H */
