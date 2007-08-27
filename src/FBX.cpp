/**
 * @file FBX.cpp
 * @brief Core FBX implementation
 * @author Christopher Han
 *
 * Core FBX app class implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/cmdline.h>
#include <wx/timer.h>
#endif

#include <iostream>

#include "FBX.h"
#include "FBXFrame.h"
#include "FBXEngine.h"
#include "FBXUtil.h"
#include "config/ConfigFactory.h"

/**
 * @brief UI update frequency
 */
#define UIUPDATE 500

/**
 * Definition of commandline options
 */
const wxCmdLineEntryDesc cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, wxT("h"), wxT("help"), wxT("Display usage info"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
	{ wxCMD_LINE_SWITCH, wxT("V"), wxT("version"), wxT("Display version and feature info") },
	{ wxCMD_LINE_SWITCH, wxT("v"), wxT("verbose"), wxT("Verbose execution") },
	{ wxCMD_LINE_OPTION, wxT("c"), wxT("console"), wxT("Console play one song (no GUI)") },
	{ wxCMD_LINE_NONE }
};

/**
 * Event handler table
 */
BEGIN_EVENT_TABLE(fbx::FBX, wxApp)
	EVT_TIMER(FBX_app_timer, fbx::FBX::OnTimer)
END_EVENT_TABLE()

IMPLEMENT_APP(fbx::FBX)

/**
 * Called on initialization of the application
 */
bool fbx::FBX::OnInit()
{
	if (!ParseCmdLine())
		return false;
	FBXUtil::SeedRand();
	engine = new engine::FBXEngine();
	if (console) {
		std::string cs(consolesong.mb_str());
		engine->Play(cs);
		timer = new wxTimer(this,FBX_app_timer);
		timer->Start(UIUPDATE);
		char i;
		while (engine) {
//			i == std::cin.get();
//			i = toupper(i);
//			if (i == 'Q')
//				return false;
			std::cout << engine->StatusString() << std::endl;
			usleep(UIUPDATE * 1000);
		}
	} else {
		frame = new FBXFrame();
		timer = new wxTimer(frame,FBX_frame_timer);
		timer->Start(UIUPDATE);
		frame->engine = engine;
		frame->Show(true);
		frame->OpenSavedPlaylists(config::ConfigFactory::GetConfig().GetString("playlists",""));
		SetTopWindow(frame);
		SetExitOnFrameDelete(true);
	}
	return true;
}

/**
 * Called on termination of the application
 */
int fbx::FBX::OnExit()
{
	if (timer)
		timer->Stop();
	if (engine) {
		engine->Stop();
		delete engine;
	}
	config::ConfigFactory::Deallocate();
	return 0;
}

/**
 * This parses the given commandline options and sets appropriate flags
 */
bool fbx::FBX::ParseCmdLine()
{
	wxCmdLineParser cmd(cmdLineDesc, argc, argv);
	cmd.SetLogo(wxT(PACKAGE_STRING));
	if (cmd.Parse(true))
		return false;
	if (cmd.Found(wxT("V"))) {
		std::cout << PACKAGE_STRING << std::endl;
		return false;
	}
	console = cmd.Found(wxT("c"),&consolesong);
	verbose = cmd.Found(wxT("v"));
	return true;
}

/**
 * Called to return the verbosity of the app
 */
bool fbx::FBX::GetVerbose() const
{
	return verbose;
}

/**
 * Called when update timer fires
 */
void fbx::FBX::OnTimer(wxTimerEvent &event)
{
	std::cout << "FBX::OnTimer" << std::endl;
	if (engine) {
		if (!engine->Eof())
			std::cout << engine->StatusString() << std::endl;
		else
			ExitMainLoop();
	}
}
