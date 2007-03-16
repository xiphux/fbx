/**
 * @file ConfigDotfile.cpp
 * @brief Linux Dotfile config implementation
 * @author Christopher Han
 *
 * Linux home directory dotfile configuration class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "ConfigDotfile.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <iostream>

/**
 * Constructor
 * Loads an existing config into memory if one exists
 * Creates dir and config file if nonexistent
 */
fbx::ConfigDotfile::ConfigDotfile(std::string dir, std::string fname)
{
	mkdir(dir.c_str(),0755);
	filename = dir.append("/").append(fname);
	std::ifstream reader(filename.c_str());
	if (reader.good()) {
		int idx;
		std::string read;
		while (getline(reader,read))
			if ((idx = read.find_first_of("=")) > 0)
				data[read.substr(0,idx)] = read.substr(idx+1);
		reader.close();
	}
	file.open(filename.c_str());
	if (!file)
		std::cerr << "[ConfigDotfile] Could not open config file: " << filename << std::endl;
	Flush();
}

/**
 * Destructor
 * Cleans up open file references
 */
fbx::ConfigDotfile::~ConfigDotfile()
{
	Flush();
	file.close();
}

/**
 * Sets a key to a given integer value
 */
void fbx::ConfigDotfile::SetInt(std::string name, unsigned int value)
{
	std::stringstream ss;
	ss << value;
	data[name] = ss.str();
	Flush();
}

/**
 * Sets a key to a given string value
 */
void fbx::ConfigDotfile::SetString(std::string name, std::string value)
{
	data[name] = value;
	Flush();
}

/**
 * Attempts to get an integer key value, or gives default if not found
 */
unsigned int fbx::ConfigDotfile::GetInt(std::string name, unsigned int def)
{
	std::map<std::string,std::string>::iterator pos = data.find(name);
	return ( pos == data.end() ? def : atoi(data[name].c_str()) );
}

/**
 * Attempts to get a string key value, or gives default if not found
 */
std::string fbx::ConfigDotfile::GetString(std::string name, std::string def)
{
	std::map<std::string,std::string>::iterator pos = data.find(name);
	return ( pos == data.end() ? def : data[name] );
}

/**
 * Flushes in-memory data to disk
 */
void fbx::ConfigDotfile::Flush()
{
	Truncate();
	for(std::map<std::string,std::string>::iterator iter = data.begin(); iter != data.end(); iter++)
		file << iter->first << "=" << iter->second << std::endl;
	file.flush();
}

/**
 * Truncates existing config file to 0
 * (to avoid trailing characters)
 */
void fbx::ConfigDotfile::Truncate()
{
	if (file)
		file.close();
	file.open(filename.c_str(),std::ios::out|std::ios::trunc);
}
