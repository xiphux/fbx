/*
 * AudioFileFactory.h
 * AudioFile Factory definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_AUDIOFILEFACTORY_H
#define FBX_AUDIOFILEFACTORY_H

#include <string>
#include "AudioFileBase.h"

namespace fbx
{

	class AudioFileFactory
	{
	public:
		static bool IsAudioFile(const std::string& filename);
		static unsigned int AudioFileType(const std::string& filename);
		static AudioFileBase *OpenAudioFile(const std::string& filename);
	protected:
		static unsigned int AudioFileTypeByExtension(const std::string& filename);
		static unsigned int AudioFileTypeByMagic(const std::string& filename);
	};

}

#endif /* FBX_AUDIOFILEFACTORY_H */
