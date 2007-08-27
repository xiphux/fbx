/**
 * @file RingBuffer.h
 * @brief Ringbuffer definition
 * @author Christopher Han
 *
 * Basic ringbuffer class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_RINGBUFFER_H
#define FBX_RINGBUFFER_H

namespace fbx
{

	/**
	 * @brief RingBuffer class
	 */
	class RingBuffer
	{
	public:
		/**
		 * @brief Constructor
		 * @param sz size of buffer
		 */
		RingBuffer(const unsigned int sz);

		/**
		 * @brief Destructor
		 */
		virtual ~RingBuffer();

		/**
		 * @brief Read
		 * @param buf space to read into
		 * @param len amount to read
		 * @return amount read
		 *
		 * Read data from buffer
		 */
		unsigned int Read(char *buf, const unsigned int len);

		/**
		 * @brief Write
		 * @param buf data to write in
		 * @param len amount to write
		 * @return amount written
		 *
		 * Write data into buffer
		 */
		unsigned int Write(char *buf, const unsigned int len);

		/**
		 * @brief Size
		 * @return size of buffer
		 *
		 * Get size of buffer
		 */
		unsigned int Size() const;

		/**
		 * @brief Len
		 * @return length of data
		 *
		 * Length of data in buffer
		 */
		unsigned int Len() const;

		/**
		 * @brief Empty
		 * @return whether buffer is empty
		 *
		 * Test whether buffer is empty
		 */
		bool Empty() const;

		/**
		 * @brief Clear
		 *
		 * Clear data in buffer
		 */
		void Clear();

	protected:
		/**
		 * @brief data
		 *
		 * Pointer to storage space
		 */
		char *data;

		/**
		 * @brief loadptr
		 *
		 * Pointer to end of valid data
		 */
		unsigned int loadptr;

		/**
		 * @brief consumeptr
		 *
		 * Pointer to beginning of valid data
		 */
		unsigned int consumeptr;

		/**
		 * @brief size
		 *
		 * Size of buffer
		 */
		unsigned int size;

		/**
		 * @brief datacount
		 *
		 * Amount of data in buffer
		 */
		unsigned int datacount;
	};

}

#endif /* FBX_RINGBUFFER_H */
