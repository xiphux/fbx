/**
 * @file AudioFileFactory.h
 * @brief AudioFile Factory definition
 * @author Christopher Han
 *
 * Audiofile factory and utility class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFILEFACTORY_H
#define FBX_AUDIOFILEFACTORY_H

#include <string>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "AudioFileBase.h"

namespace fbx
{

	namespace audiofile
	{

		/**
		 * @brief Audiofile factory and utility class
		 */
		class AudioFileFactory
		{
		public:
			/**
			 * @brief Is Audio File
			 * @param filename file to test
			 * @return whether input is an audio file
			 *
			 * Tests whether given file is a recognized audio file format
			 */
			static bool IsAudioFile(const std::string& filename);

			/**
			 * @brief Audio File Type
			 * @param filename file to test
			 * @return type of audio file given
			 *
			 * Attempts to determine the type of audio file given (or NONE if unrecognized)
			 */
			static unsigned int AudioFileType(const std::string& filename);

			/**
			 * @brief Open Audio File
			 * @param filename file to open
			 * @return audiofile reader for given file
			 *
			 * Attempts to return an audiofile reader appropriate for the given filename
			 */
			static AudioFileBase *OpenAudioFile(const std::string& filename);

			/**
			 * @brief Extensions
			 * @return list of recognized audio file extensions
			 *
			 * Returns a semicolon-delimited list of recognized audiofile extensions
			 * (for use in open dialogs)
			 */
			static std::string Extensions();

		protected:
			/**
			 * @brief Audio File Type By Extension
			 * @param filename file to test
			 * @return type of audio file given
			 *
			 * Attempts to determine the type of the given audio file using its extension
			 */
			static unsigned int AudioFileTypeByExtension(const std::string& filename);

#ifdef HAVE_MAGIC
			/**
			 * @brief Audio File Type By Magic
			 * @param filename file to test
			 * @return type of audio file given
			 *
			 * Attempts to determine the type of the given audio file using libmagic
			 * to test the file magic and get the mime type
			 */
			static unsigned int AudioFileTypeByMagic(const std::string& filename);
#endif
		};

	}

}

#endif /* FBX_AUDIOFILEFACTORY_H */
