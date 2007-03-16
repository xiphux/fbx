/**
 * @file ConfigFactory.cpp
 * @brief Config Factory implementation
 * @author Christopher Han
 *
 * Config factory and utility class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#include "ConfigFactory.h"

#include "ConfigDotfile.h"

/**
 * Singleton instance of config
 */
fbx::ConfigBase* fbx::ConfigFactory::instance = 0;

/**
 * Returns config instance appropriate for platform,
 * instantiating one if necessary
 */
fbx::ConfigBase& fbx::ConfigFactory::GetConfig()
{
	if (!instance) {
		instance = new ConfigDotfile();
	}
	return *instance;
}

/**
 * Deallocates existing config instance
 */
void fbx::ConfigFactory::Deallocate()
{
	if (instance)
		delete instance;
	instance = 0;
}
