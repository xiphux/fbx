/**
 * @file AudioBase.h
 * @brief Base Audio definition
 * @author Christopher Han
 *
 * Base abstract audio driver class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOBASE_H
#define FBX_AUDIOBASE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/**
 * @brief null audio
 *
 * Null audio driver
 */
#define FBX_AUDIO_NONE 0

#ifdef HAVE_AO
/**
 * @brief libao audio
 *
 * Libao audio output driver
 */
#define FBX_AUDIO_AO 1
#endif

#ifdef HAVE_ALSA
/**
 * @brief alsa audio
 *
 * ALSA audio output driver
 */
#define FBX_AUDIO_ALSA 2
#endif

namespace fbx
{

	namespace audio
	{

		/**
		 * @brief Abstract base audio driver class
		 *
		 * All audio driver classes must inherit from this
		 */
		class AudioBase
		{
		public:
			/**
			 * @brief Destructor
			 */
			virtual ~AudioBase() {};

			/**
			 * @brief Opened
			 * @return whether audio output is open
			 *
			 * Returns whether audio output driver is open and ready
			 */
			virtual bool Opened() const {return opened;};

			/**
			 * @brief Write
			 * @param buf buffer of audio data to write
			 * @param len length of audio data to write
			 * @return amount written
			 *
			 * Write audio data to output driver
			 * Must be implemented
			 */
			virtual long Write(char *buf, long len) = 0;

		protected:
			/**
			 * @brief opened
			 *
			 * Flag whether audio output is open and ready
			 */
			bool opened;
		};

	}

}

#endif /* FBX_AUDIOBASE_H */
