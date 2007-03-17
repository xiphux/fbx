/**
 * @file ConfigFactory.h
 * @brief Config Factory definition
 * @author Christopher Han
 *
 * Config factory and utility class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_CONFIGFACTORY_H
#define FBX_CONFIGFACTORY_H

#include "ConfigBase.h"

namespace fbx
{

	namespace config
	{

		/**
		 * @brief Config factory and utility class
		 */
		class ConfigFactory
		{
		public:
			/**
			 * @brief Get Config
			 * @return singleton instance of config
			 *
			 * Returns config instance appropriate for platform,
			 * instantiating one if necessary
			 */
			static ConfigBase& GetConfig();

			/**
			 * @brief Deallocate
			 *
			 * Deallocates existing config instance
			 */
			static void Deallocate();

		protected:
			/**
			 * @brief instance
			 * 
			 * Singleton instance of config
			 */
			static ConfigBase* instance;
		};

	}

}

#endif /* FBX_CONFIGFACTORY_H */
