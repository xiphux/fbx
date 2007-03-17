/*
 * fbxtest.cpp
 * FBX test program
 * Copyright (C) 2007 Christopher Han
 */

#include <iostream>
#include <string>
#include "audio/AudioFactory.h"
#include "audiofile/AudioFileFactory.h"

#define BUFSIZE 2048

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cout << "Requires an argument" << std::endl;
		return 1;
	}
	fbx::audio::AudioBase *audio = fbx::audio::AudioFactory::CreateAudio();
	if (!audio) {
		std::cout << "Could not create audio output" << std::endl;
		return 2;
	}
	std::string fname = argv[1];
	if (!fbx::audiofile::AudioFileFactory::IsAudioFile(fname)) {
		std::cout << "Not a recognized audio file" << std::endl;
		return 2;
	}
	fbx::audiofile::AudioFileBase *audiofile = fbx::audiofile::AudioFileFactory::OpenAudioFile(fname);
	if (!audiofile) {
		std::cout << "Error opening audiofile" << std::endl;
		return 2;
	}
	char buf[BUFSIZE];
	int len = 0;
	while (!audiofile->Eof()) {
		len = audiofile->Read(buf, BUFSIZE);
		if (len < 0) {
			std::cout << "Error reading audiofile" << std::endl;
			break;
		} else {
			std::cout << "Read: " << len << std::endl;
			if (!audio->Write(buf, len))
				std::cout << "Error writing " << len << std::endl;
		}
	}
	delete audiofile;
	delete audio;
	return 0;
}
