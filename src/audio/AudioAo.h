/**
 * @file AudioAo.h
 * @brief Libao Audio definition
 * @author Christopher Han
 *
 * Libao audio driver class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOAO_H
#define FBX_AUDIOAO_H

#include "AudioBase.h"
#include <ao/ao.h>

namespace fbx
{

	namespace audio
	{

		/**
		 * @brief Libao output driver
		 *
		 * Derives from AudioBase
		 */
		class AudioAo: public AudioBase
		{
		public:
			/**
			 * @brief Constructor
			 *
			 * Initializes libao
			 */
			AudioAo();

			/**
			 * @brief Destructor
			 *
			 * Closes libao
			 */
			virtual ~AudioAo();

			/**
			 * @brief Write
			 * @param buf buffer of audio data to write
			 * @param len length of audio data to write
			 * @return amount written
			 *
			 * Write audio data to libao
			 */
			virtual long Write(char *buf, long len);

		protected:
			/**
			 * @brief device
			 *
			 * Libao open device pointer
			 */
			ao_device *device;
		};

	}

}

#endif /* FBX_AUDIOAO_H */
