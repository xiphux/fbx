/*
 * AudioFileFlac.cpp
 * FLAC AudioFile implementation
 * Copyright (C) 2007 Christopher Han
 */

#include <iostream>
#include "AudioFileFlac.h"

static void flac_callback_metadata(const FLAC__SeekableStreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{
}

static void flac_callback_error(const FLAC__SeekableStreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
}

static FLAC__StreamDecoderWriteStatus flac_callback_write(const FLAC_SeekableStreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32* const buffer[], void *client_data)
{
}

fbx::AudioFileFlac::AudioFileFlac(const std::string& fname):
	AudioFileBase(fname)
{
	opened = false;
	fp = fopen(fname.c_str(), "rb");
	if (!fp) {
		std::cerr << "[AudioFileFlac] Error opening file: " << fname << std::endl;
		return;
	}
	decoder = FLAC__seekable_stream_decoder_new();
	opened = true;
}

fbx::AudioFileFlac::~AudioFileFlac()
{
	FLAC__seekable_stream_decoder_finish(decoder);
	FLAC__seekable_stream_decoder_delete(decoder);
}

int fbx::AudioFileFlac::Seek(double pos)
{
}

long fbx::AudioFileFlac::Read(char *buf, long len)
{
}

double fbx::AudioFileFlac::Size()
{
}

double fbx::AudioFileFlac::Current()
{
}

bool fbx::AudioFileFlac::Eof()
{
}

std::string fbx::AudioFileFlac::InfoString()
{
}

std::string fbx::AudioFileFlac::Metadata(const unsigned int field)
{
}
