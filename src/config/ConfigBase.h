/**
 * @file ConfigBase.h
 * @brief Base Configuration definition
 * @author Christopher Han
 * 
 * Abstract config base class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_CONFIGBASE_H
#define FBX_CONFIGBASE_H

#include <string>

namespace fbx
{

	/**
	 * @brief Abstract config base class
	 *
	 * All platform-specific config classes must inherit from this
	 */
	class ConfigBase
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~ConfigBase() {};

		/**
		 * @brief Set Int
		 * @param name name of key to set
		 * @param value integer value to set
		 * 
		 * Sets a key to a given integer value
		 * Must be implemented
		 */
		virtual void SetInt(std::string name, unsigned int value) = 0;

		/**
		 * @brief Set String
		 * @param name name of key to set
		 * @param value string value to set
		 *
		 * Sets a key to a given string value
		 * Must be implemented
		 */
		virtual void SetString(std::string name, std::string value) = 0;

		/**
		 * @brief Get Int
		 * @param name name of key to get
		 * @param def default value to return if not found
		 * @return integer value if found, default value if not
		 *
		 * Attempts to get an integer key value, or gives default if not found
		 * Must be implemented
		 */
		virtual unsigned int GetInt(std::string name, unsigned int def) = 0;

		/**
		 * @brief Get String
		 * @param name name of key to get
		 * @param def default value to return if not found
		 * @return string value if found, default value if not
		 *
		 * Attempts to get a string key value, or gives default if not found
		 * Must be implemented
		 */
		virtual std::string GetString(std::string name, std::string def) = 0;
	};

}

#endif /* FBX_CONFIGBASE_H */
