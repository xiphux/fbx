/**
 * @file AudioFileBase.h
 * @brief Base AudioFile definition
 * @author Christopher Han
 *
 * Base abstract audiofile class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFILEBASE_H
#define FBX_AUDIOFILEBASE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

/**
 * @brief null audiofile
 *
 * Null audiofile
 */
#define FBX_AUDIOFILE_NONE 0

#ifdef HAVE_VORBIS
/**
 * @brief Vorbis audiofile
 *
 * Ogg Vorbis audiofile
 */
#define FBX_AUDIOFILE_VORBIS 1
#endif

#ifdef HAVE_FLAC
/**
 * @brief FLAC audiofile
 *
 * FLAC audiofile
 */
#define FBX_AUDIOFILE_FLAC 2
#endif


/**
 * @brief null metadata
 *
 * Null metadata field
 */
#define FBX_METADATA_NONE 0

/**
 * @brief artist metadata
 *
 * Artist metadata field
 */
#define FBX_METADATA_ARTIST 1

/**
 * @brief album metadata
 *
 * Album metadata field
 */
#define FBX_METADATA_ALBUM 2

/**
 * @brief track metadata
 *
 * Track number metadata field
 */
#define FBX_METADATA_TRACK 3

/**
 * @brief title metadata
 *
 * Track title metadata field
 */
#define FBX_METADATA_TITLE 4

namespace fbx
{

	namespace audiofile
	{

		/**
		 * @brief Abstract audiofile class
		 *
		 * All audiofile class must inherit from this
		 */
		class AudioFileBase
		{
		public:
			/**
			 * @brief Constructor
			 * @param fname filename to open
			 */
			AudioFileBase(const std::string& fname);

			/**
			 * @brief Destructor
			 */
			virtual ~AudioFileBase();

			/**
			 * @brief Opened
			 * @return whether file is opened
			 *
			 * Tests whether audiofile is successfully opened
			 */
			virtual bool Opened() const;

			/**
			 * @brief Seek
			 * @param pos position to seek to in seconds
			 * @return whether seek was successful
			 *
			 * Attempts to seek to the given position
			 * Must be implemented
			 */
			virtual int Seek(double pos) = 0;

			/**
			 * @brief Read
			 * @param buf buffer to read into
			 * @param len amount of data to read
			 * @return amount of data read
			 *
			 * Attempts to read audio data from audiofile into buffer
			 * Must be implemented
			 */
			virtual long Read(char *buf, long len) = 0;

			/**
			 * @brief Size
			 * @return size of audiofile
			 * 
			 * Returns the size of the loaded audiofile
			 * Must be implemented
			 */
			virtual double Size() = 0;

			/**
			 * @brief Current
			 * @return current position of audiofile
			 *
			 * Returns the current position of the playing audiofile
			 * Must be implemented
			 */
			virtual double Current() = 0;

			/**
			 * @brief End of file
			 * @return whether the audiofile is at the end of file
			 *
			 * Tests whether the audiofile has reached the EOF
			 * Must be implemented
			 */
			virtual bool Eof() = 0;

			/**
			 * @brief Info String
			 * @return string of info about file
			 *
			 * Returns a string of info about the audiofile
			 * (format, bitrate, sampling rate, channels, etc)
			 * Must be implemented
			 */
			virtual std::string InfoString() = 0;

			/**
			 * @brief Metadata
			 * @param field metadata field to fetch
			 * @return string of metadata requested
			 *
			 * Fetches and returns a specific field of metadata
			 * Must be implemented
			 */
			virtual std::string Metadata(const unsigned int field) = 0;

			/**
			 * @brief Metadata String
			 * @return string of metadata info
			 *
			 * Returns a formatted string of a number of common metadata fields
			 */
			virtual std::string MetadataString();

			/**
			 * @brief Filename
			 * @return current filename
			 *
			 * Returns the currently open filename
			 */
			std::string Filename() const;

		protected:
			/**
			 * @brief filename
			 *
			 * Stores the opened file's filename
			 */
			std::string filename;

			/**
			 * @brief opened
			 *
			 * Flag indicating whether file was successfully opened
			 */
			bool opened;
		};

	}

}

#endif /* FBX_AUDIOFILEBASE_H */
