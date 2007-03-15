/*
 * FBXUtil.h
 * FBX utilities definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXUTIL_H
#define FBX_FBXUTIL_H

#include <string>

namespace fbx
{

	class FBXUtil
	{
	public:
		static std::string ReadableTime(const double d);
		static std::string ReadableTime(const int i);
	};

}

#endif /* FBX_FBXUTIL_H */
