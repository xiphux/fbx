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
	fbx::audiofile::AudioFileFlac *data = (fbx::audiofile::AudioFileFlac*)client_data;
	switch (metadata->type) {
		case FLAC__METADATA_TYPE_STREAMINFO:
			data->fileinfo.bits_per_sample = metadata->data.stream_info.bits_per_sample;
			data->fileinfo.sample_rate = metadata->data.stream_info.sample_rate;
			data->fileinfo.channels = metadata->data.stream_info.channels;
			data->fileinfo.total_samples = metadata->data.stream_info.total_samples;
			break;
		case FLAC__METADATA_TYPE_VORBIS_COMMENT:
			data->vorbiscomment = FLAC__metadata_object_clone(metadata);
			break;
	}
}

static void flac_callback_error(const FLAC__SeekableStreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
	std::cerr << "[AudioFileFlac] Error: " << FLAC__StreamDecoderErrorStatusString[status] << std::endl;
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
	FLAC__SeekableStreamDecoderInitStatus stat = FLAC__seekable_stream_decoder_init_FILE(decoder,fp,flac_callback_write,flac_callback_metadata,flac_callback_error,this);
	if (stat != FLAC__SEEKABLE_STREAM_DECODER_OK) {
		std::cerr << "[AudioFileFlac] Error initializing FLAC decoder: " << FLAC__seekable_stream_decoder_get_resolved_state_string (decoder) << std::endl;
		return;
	}
	FLAC__bool retval = FLAC__seekable_stream_decoder_process_until_end_of_metadata(decoder);
	if (!retval) {
		std::cerr << "[AudioFileFlac] Error reading metadata" << std::endl;
		return;
	}
	opened = true;
}

/**
 * Destructor
 * Closes file
 */
fbx::audiofile::AudioFileFlac::~AudioFileFlac()
{
	if (vorbiscomment)
		FLAC__metadata_object_delete(vorbiscomment);
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
