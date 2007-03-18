/**
 * @file AudioFileFlac.cpp
 * @brief FLAC AudioFile implementation
 * @author Christopher Han
 *
 * FLAC audiofile class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
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

/**
 * Constructor
 * Opens file
 */
fbx::audiofile::AudioFileFlac::AudioFileFlac(const std::string& fname):
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

/**
 * Destructor
 * Closes file
 */
fbx::audiofile::AudioFileFlac::~AudioFileFlac()
{
	FLAC__seekable_stream_decoder_finish(decoder);
	FLAC__seekable_stream_decoder_delete(decoder);
}

/**
 * Attempts to seek to the given position
 */
int fbx::audiofile::AudioFileFlac::Seek(double pos)
{
}

/**
 * Attempts to read audio data from FLAC file into buffer
 */
long fbx::audiofile::AudioFileFlac::Read(char *buf, long len)
{
}

/**
 * Returns the size of the loaded FLAC file
 */
double fbx::audiofile::AudioFileFlac::Size()
{
}

/**
 * Returns the current position of the playing FLAC file
 */
double fbx::audiofile::AudioFileFlac::Current()
{
}

/**
 * Tests whether the FLAC file has reached the EOF
 */
bool fbx::audiofile::AudioFileFlac::Eof()
{
}

/**
 * Returns a string of info about the FLAC file
 * (format, bitrate, sampling rate, channels, etc)
 */
std::string fbx::audiofile::AudioFileFlac::InfoString()
{
}

/**
 * Fetches and returns a specific field of metadata
 */
std::string fbx::audiofile::AudioFileFlac::Metadata(const unsigned int field)
{
}
