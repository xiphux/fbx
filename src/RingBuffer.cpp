/**
 * @file RingBuffer.cpp
 * @brief Ringbuffer implementation
 * @author Christopher Han
 *
 * Basic ringbuffer class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "RingBuffer.h"

#include <string.h>

/**
 * Constructor
 */
fbx::RingBuffer::RingBuffer(const unsigned int sz):
	size(sz),
	datacount(0),
	loadptr(0),
	consumeptr(0)
{
	data = new char[size];
}

/**
 * Destructor
 */
fbx::RingBuffer::~RingBuffer()
{
	delete [] data;
}

/**
 * Read data from buffer
 */
unsigned int fbx::RingBuffer::Read(char *buf, const unsigned int len)
{
	if (!buf)
		return 0;
	unsigned int read;
	for (read = 0; read < len; read++) {
		if (datacount == 0)
			break;
		buf[read] = data[consumeptr++];
		datacount--;
		if (consumeptr == size)
			consumeptr = 0;
	}
	return read;
}

/**
 * Write data into buffer
 */
unsigned int fbx::RingBuffer::Write(char *buf, const unsigned int len)
{
	if (!buf)
		return 0;
	unsigned int wrote;
	for (wrote = 0; wrote < len; wrote++) {
		if (datacount == size)
			break;
		data[loadptr++] = buf[wrote];
		datacount++;
		if (loadptr == size)
			loadptr = 0;
	}
	return wrote;
}

/**
 * Get size of buffer
 */
unsigned int fbx::RingBuffer::Size() const
{
	return size;
}

/**
 * Length of data in buffer
 */
unsigned int fbx::RingBuffer::Len() const
{
	return datacount;
}

/**
 * Test whether buffer is empty
 */
bool fbx::RingBuffer::Empty() const
{
	return datacount == 0;
}

/**
 * Clear data in buffer
 */
void fbx::RingBuffer::Clear()
{
	memset(data,'\0',sizeof(data));
}
