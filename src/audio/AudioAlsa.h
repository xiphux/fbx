/**
 * @file AudioAlsa.h
 * @brief Alsa Audio definition
 * @author Christopher Han
 *
 * ALSA audio driver class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOALSA_H
#define FBX_AUDIOALSA_H

#include "AudioBase.h"
#include <asoundlib.h>

namespace fbx
{

	namespace audio
	{

		/**
		 * @brief ALSA output driver
		 *
		 * Derives from AudioBase
		 */
		class AudioAlsa: public AudioBase
		{
		public:
			/**
			 * @brief Constructor
			 *
			 * Initializes ALSA
			 */
			AudioAlsa();

			/**
			 * @brief Destructor
			 *
			 * Closes ALSA
			 */
			virtual ~AudioAlsa();

			/**
			 * @brief Write
			 * @param buf buffer of audio data to write
			 * @param len length of audio data to write
			 * @return amount written
			 *
			 * Write audio data to ALSA
			 */
			virtual long Write(char *buf, long len);

		protected:
			/**
			 * @brief handle
			 *
			 * Pointer to open ALSA device handle
			 */
			snd_pcm_t *handle;
		};

	}

}

#endif /* FBX_AUDIOALSA_H */
