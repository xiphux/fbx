/**
 * @file FBXUtil.h
 * @brief FBX utilities definition
 * @author Christopher Han
 *
 * Utility function toolbox class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_FBXUTIL_H
#define FBX_FBXUTIL_H

#include <string>

namespace fbx
{

	/**
	 * @brief FBX utility toolbox class
	 */
	class FBXUtil
	{
	public:
		/**
		 * @brief Readable time
		 * @param d input time in seconds
		 *
		 * Formats time in seconds into standard mm:ss time string
		 */
		static std::string ReadableTime(const double d);

		/**
		 * @brief Readable time
		 * @param i input time in seconds
		 *
		 * Formats time in seconds into standard mm:ss time string
		 */
		static std::string ReadableTime(const int i);

		/**
		 * @brief Seed Rand
		 *
		 * Seeds the random number generator
		 */
		static void SeedRand();

		/**
		 * @brief Rand
		 * @param lower lower bound
		 * @param upper upper bound
		 * @return integer between bounds
		 *
		 * Returns a random number between the given lower/upper bound
		 */
		static int Rand(const int lower, const int upper);
	};

}

#endif /* FBX_FBXUTIL_H */
