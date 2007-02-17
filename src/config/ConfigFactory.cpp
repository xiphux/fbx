/*
 * ConfigFactory.cpp
 * Config Factory implementation
 * Copyright (C) 2007 Christopher Han
 */
#include "ConfigFactory.h"

#include "ConfigDotfile.h"

fbx::ConfigBase* fbx::ConfigFactory::instance = 0;

fbx::ConfigBase& fbx::ConfigFactory::GetConfig()
{
	if (!instance) {
		instance = new ConfigDotfile();
	}
	return *instance;
}

void fbx::ConfigFactory::Deallocate()
{
	if (instance)
		delete instance;
	instance = 0;
}
