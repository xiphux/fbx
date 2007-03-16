/**
 * @file FBXUtil.cpp
 * @brief FBX utilities implementation
 * @author Christopher Han
 *
 * Utility function toolbox class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "FBXUtil.h"

#include <sstream>
#include <cstdlib>
#include <time.h>

/**
 * Formats time in seconds into standard mm:ss time string
 */
std::string fbx::FBXUtil::ReadableTime(const double d)
{
	return ReadableTime((int)d);
}

/**
 * Formats time in seconds into standard mm:ss time string
 */
std::string fbx::FBXUtil::ReadableTime(const int i)
{
	int s = i;
	int m = 0;
	while (s >= 60) {
		m++;
		s -= 60;
	}
	std::stringstream str;
	str << m;
	str << ":";
	if (s < 10)
		str << 0;
	str << s;
	return str.str();
}

/**
 * Seeds the random number generator
 */
void fbx::FBXUtil::SeedRand()
{
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);
}

/**
 * Returns a random number between the given lower/upper bound
 */
int fbx::FBXUtil::Rand(const int lower, const int upper)
{
	return (int)(rand() % (upper - lower + 1) + lower);
}
