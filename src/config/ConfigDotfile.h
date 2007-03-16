/**
 * @file ConfigDotfile.h
 * @brief Linux Dotfile config definition
 * @author Christopher Han
 *
 * Linux home directory dotfile configuration class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_CONFIGDOTFILE_H
#define FBX_CONFIGDOTFILE_H

#include "ConfigBase.h"

#include <fstream>
#include <map>

/**
 * @brief dot config file
 * 
 * Filename of config file to use
 */
#define DOTCONFIGFILE "fbxrc"

/**
 * @brief dot config dir
 *
 * Name of directory to use inside user's home directory
 */
#define DOTCONFIGDIR ".fbx"

/**
 * @brief dot config path
 *
 * Full path (including user's home directory) to dot config dir
 */
#define DOTCONFIGPATH (std::string(getenv("HOME")).append("/").append(DOTCONFIGDIR))

namespace fbx
{

	/**
	 * @brief Linux dotfile class
	 *
	 * Derives from ConfigBase
	 */
	class ConfigDotfile: public ConfigBase
	{
	public:
		/**
		 * @brief Constructor
		 * @param dir directory to write in
		 * @param fname filename to use
		 *
		 * Loads an existing config into memory if one exists
		 * Creates dir and config file if nonexistent
		 */
		ConfigDotfile(std::string dir = DOTCONFIGPATH, std::string fname = DOTCONFIGFILE);

		/**
		 * @brief Destructor
		 *
		 * Cleans up open file references
		 */
		virtual ~ConfigDotfile();

		/**
		 * @brief Set Int
		 * @param name name of key to set
		 * @param value integer value to set
		 * 
		 * Sets a key to a given integer value
		 */
		virtual void SetInt(std::string name, unsigned int value);

		/**
		 * @brief Set String
		 * @param name name of key to set
		 * @param value string value to set
		 *
		 * Sets a key to a given string value
		 */
		virtual void SetString(std::string name, std::string value);

		/**
		 * @brief Get Int
		 * @param name name of key to get
		 * @param def default value to return if not found
		 * @return integer value if found, default value if not
		 *
		 * Attempts to get an integer key value, or gives default if not found
		 */
		virtual unsigned int GetInt(std::string name, unsigned int def);

		/**
		 * @brief Get String
		 * @param name name of key to get
		 * @param def default value to return if not found
		 * @return string value if found, default value if not
		 *
		 * Attempts to get a string key value, or gives default if not found
		 */
		virtual std::string GetString(std::string name, std::string def);

	protected:
		/**
		 * @brief filename
		 *
		 * Full filename of config file
		 */
		std::string filename;

		/**
		 * @brief file
		 *
		 * Output file stream
		 */
		std::ofstream file;

		/**
		 * @brief data
		 *
		 * Map of key-value pairs
		 */
		std::map<std::string, std::string> data;

		/**
		 * @brief Flush
		 *
		 * Flushes in-memory data to disk
		 */
		virtual void Flush();

		/**
		 * @brief Truncate
		 *
		 * Truncates existing config file to 0
		 * (to avoid trailing characters)
		 */
		virtual void Truncate();
	};

}

#endif /* FBX_CONFIGDOTFILE_H */
