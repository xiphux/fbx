/*
 * ConfigDotfile.h
 * Linux Dotfile config definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_CONFIGDOTFILE_H
#define FBX_CONFIGDOTFILE_H

#include "ConfigBase.h"

#include <fstream>
#include <map>

#define DOTCONFIGFILE "fbxrc"

#define DOTCONFIGDIR ".fbx"

#define DOTCONFIGPATH (std::string(getenv("HOME")).append("/").append(DOTCONFIGDIR))

namespace fbx
{

	class ConfigDotfile: public ConfigBase
	{
	public:
		ConfigDotfile(std::string dir = DOTCONFIGPATH, std::string fname = DOTCONFIGFILE);
		virtual ~ConfigDotfile();
		virtual void SetInt(std::string name, unsigned int value);
		virtual void SetString(std::string name, std::string value);
		virtual unsigned int GetInt(std::string name, unsigned int def);
		virtual std::string GetString(std::string name, std::string def);
	protected:
		std::string filename;
		std::ofstream file;
		std::map<std::string, std::string> data;
		virtual void Flush();
		virtual void Truncate();
	};

}

#endif /* FBX_CONFIGDOTFILE_H */
