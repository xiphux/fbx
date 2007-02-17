/*
 * ConfigBase.h
 * Base Configuration definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_CONFIGBASE_H
#define FBX_CONFIGBASE_H

#include <string>

namespace fbx
{

	class ConfigBase
	{
	public:
		virtual ~ConfigBase() {};
		virtual void SetInt(std::string name, unsigned int value) = 0;
		virtual void SetString(std::string name, std::string value) = 0;
		virtual unsigned int GetInt(std::string name, unsigned int def) = 0;
		virtual std::string GetString(std::string name, std::string def) = 0;
	};

}

#endif /* FBX_CONFIGBASE_H */
