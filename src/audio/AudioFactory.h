/**
 * @file AudioFactory.h
 * @brief Audio Factory definition
 * @author Christopher Han
 *
 * Audio output driver factory class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_AUDIOFACTORY_H
#define FBX_AUDIOFACTORY_H

#include "AudioBase.h"

namespace fbx
{

	namespace audio
	{

		/**
		 * @brief Audio output driver factory
		 */
		class AudioFactory
		{
		public:
			/**
			 * @brief Create Audio
			 * @param type audio driver to create
			 * @return typed audio driver
			 *
			 * Creates an instance of the audio driver that was requested
			 */
			static AudioBase *CreateAudio(unsigned int type = FBX_AUDIO_NONE);

			/**
			 * @brief Default audio
			 * @return type of audio driver
			 *
			 * Returns the best audio output driver for the current platform
			 */
			static unsigned int DefaultAudio();
		};

	}

}

#endif /* FBX_AUDIOFACTORY_H */
