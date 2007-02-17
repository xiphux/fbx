/*
 * ConfigDotfile.cpp
 * Linux Dotfile config implementation
 * Copyright (C) 2007 Christopher Han
 */
#include "ConfigDotfile.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <iostream>

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

fbx::ConfigDotfile::~ConfigDotfile()
{
	Flush();
	file.close();
}

void fbx::ConfigDotfile::SetInt(std::string name, unsigned int value)
{
	std::stringstream ss;
	ss << value;
	data[name] = ss.str();
	Flush();
}

void fbx::ConfigDotfile::SetString(std::string name, std::string value)
{
	data[name] = value;
	Flush();
}

unsigned int fbx::ConfigDotfile::GetInt(std::string name, unsigned int def)
{
	std::map<std::string,std::string>::iterator pos = data.find(name);
	return ( pos == data.end() ? def : atoi(data[name].c_str()) );
}

std::string fbx::ConfigDotfile::GetString(std::string name, std::string def)
{
	std::map<std::string,std::string>::iterator pos = data.find(name);
	return ( pos == data.end() ? def : data[name] );
}

void fbx::ConfigDotfile::Flush()
{
	Truncate();
	for(std::map<std::string,std::string>::iterator iter = data.begin(); iter != data.end(); iter++)
		file << iter->first << "=" << iter->second << std::endl;
	file.flush();
}

void fbx::ConfigDotfile::Truncate()
{
	if (file)
		file.close();
	file.open(filename.c_str(),std::ios::out|std::ios::trunc);
}
