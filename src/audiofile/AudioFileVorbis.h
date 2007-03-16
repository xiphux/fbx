/**
 * @file AudioFileVorbis.h
 * @brief Vorbis AudioFile definition
 * @author Christopher Han
 *
 * Ogg Vorbis audiofile class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFILEVORBIS_H
#define FBX_AUDIOFILEVORBIS_H

#include "AudioFileBase.h"
#include "vorbis/vorbisfile.h"

namespace fbx
{

	/**
	 * @brief Ogg Vorbis audiofile class
	 *
	 * Implements AudioFileBase
	 */
	class AudioFileVorbis: public AudioFileBase
	{
	public:
		/**
		 * @brief Constructor
		 * @param fname filename to open
		 *
		 * Opens file and initializes libvorbisfile
		 */
		AudioFileVorbis(const std::string& fname);

		/**
		 * @brief Destructor
		 *
		 * Closes file and libvorbisfile
		 */
		virtual ~AudioFileVorbis();

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
		 * Attempts to read audio data from vorbis file into buffer
		 */
		virtual long Read(char *buf, long len);

		/**
		 * @brief Size
		 * @return size of vorbis file
		 * 
		 * Returns the size of the loaded vorbis file
		 */
		virtual double Size();

		/**
		 * @brief Current
		 * @return current position of vorbis file
		 *
		 * Returns the current position of the playing vorbis file
		 */
		virtual double Current();

		/**
		 * @brief End of file
		 * @return whether the vorbis file is at the end of file
		 *
		 * Tests whether the vorbis file has reached the EOF
		 */
		virtual bool Eof();

		/**
		 * @brief Info String
		 * @return string of info about file
		 *
		 * Returns a string of info about the vorbis file
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

	protected:
		/**
		 * @brief fp
		 *
		 * File pointer
		 */
		FILE *fp;

		/**
		 * @brief file
		 *
		 * Libvorbisfile ogg vorbis file pointer
		 */
		OggVorbis_File file;
	};

}

#endif /* FBX_AUDIOFILEVORBIS_H */
