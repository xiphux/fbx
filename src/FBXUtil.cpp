/*
 * FBXUtil.cpp
 * FBX utilities implementation
 * Copyright (C) 2007 Christopher Han
 */
#include "FBXUtil.h"

#include <sstream>

std::string fbx::FBXUtil::ReadableTime(const double d)
{
	return ReadableTime((int)d);
}

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
