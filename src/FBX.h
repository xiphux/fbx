/**
 * @file FBX.h
 * @brief Core FBX definition
 * @author Christopher Han
 *
 * Core FBX app class definition
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifndef FBX_FBX_H
#define FBX_FBX_H

class wxApp;

namespace fbx
{

	class FBXFrame;

	namespace engine
	{
		class FBXEngine;
	}

	/**
	 * @brief FBX app class
	 *
	 * Derives from wxApp
	 */
	class FBX: public wxApp
	{
	public:
		/**
		 * @brief OnInit
		 * @return whether initialization was successful
		 *
		 * Called on initialization of the application
		 */
		virtual bool OnInit();

		/**
		 * @brief OnExit
		 * @return exit code of app
		 *
		 * Called on termination of the application
		 */
		virtual int OnExit();

		/**
		 * @brief Get Verbose
		 * @return whether verbose option was enabled
		 *
		 * Called to return the verbosity of the app
		 */
		bool GetVerbose() const;

	protected:
		/**
		 * @brief Parse Command Line
		 * @return whether parsing was successful
		 *
		 * This parses the given commandline options and sets appropriate flags
		 */
		bool ParseCmdLine();

		/**
		 * @brief verbose
		 *
		 * Whether verbose output is enabled
		 */
		bool verbose;

		/**
		 * @brief frame
		 *
		 * Pointer to FBX window frame instance
		 */
		FBXFrame *frame;

		/**
		 * @brief engine
		 *
		 * Pointer to FBX audio engine instance
		 */
		engine::FBXEngine *engine;

		/**
		 * @brief console
		 *
		 * Whether to play in console mode
		 */
		bool console;

		/**
		 * @brief consolesong
		 *
		 * Filename to play on console
		 */
		wxString consolesong;
	};

}

#endif /* FBX_FBX_H */
