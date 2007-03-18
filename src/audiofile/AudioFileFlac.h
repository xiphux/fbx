/**
 * @file AudioFileFlac.h
 * @brief FLAC AudioFile definition
 * @author Christopher Han
 *
 * FLAC audiofile class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFILEFLAC_H
#define FBX_AUDIOFILEFLAC_H

#include "AudioFileBase.h"
#include <FLAC/all.h>

namespace fbx
{

	namespace audiofile
	{

		/**
		 * @brief FLAC audiofile class
		 *
		 * Implements AudioFileBase
		 */
		class AudioFileFlac: public AudioFileBase
		{
		public:
			/**
			 * @brief Constructor
			 * @param fname filename to open
			 *
			 * Opens file
			 */
			AudioFileFlac(const std::string& fname);

			/**
			 * @brief Destructor
			 *
			 * Closes file
			 */
			virtual ~AudioFileFlac();

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
			 * Attempts to read audio data from FLAC file into buffer
			 */
			virtual long Read(char *buf, long len);

			/**
			 * @brief Size
			 * @return size of FLAC file
			 * 
			 * Returns the size of the loaded FLAC file
			 */
			virtual double Size();

			/**
			 * @brief Current
			 * @return current position of FLAC file
			 *
			 * Returns the current position of the playing FLAC file
			 */
			virtual double Current();

			/**
			 * @brief End of file
			 * @return whether the FLAC file is at the end of file
			 *
			 * Tests whether the FLAC file has reached the EOF
			 */
			virtual bool Eof();

			/**
			 * @brief Info String
			 * @return string of info about file
			 *
			 * Returns a string of info about the FLAC file
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
			 * @brief decoder
			 *
			 * FLAC Seekable Stream Decoder pointer
			 */
			FLAC__SeekableStreamDecoder *decoder;

			FLAC__StreamMetadata *vorbiscomment;
			struct {
				unsigned int channels;
				unsigned int sample_rate;
				unsigned int bit_rate;
				unsigned int bits_per_sample;
				unsigned int total_samples;
			} fileinfo;
		};

	}

}

#endif /* FBX_AUDIOFILEFLAC_H */
