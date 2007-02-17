/*
 * ConfigFactory.h
 * Config Factory definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_CONFIGFACTORY_H
#define FBX_CONFIGFACTORY_H

#include "ConfigBase.h"

namespace fbx
{

	class ConfigFactory
	{
	public:
		static ConfigBase& GetConfig();
		static void Deallocate();
	protected:
		static ConfigBase* instance;
	};

}

#endif /* FBX_CONFIGFACTORY_H */
