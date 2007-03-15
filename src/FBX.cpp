/*
 * FBX.cpp
 * Core FBX implementation
 * Copyright (C) 2007 Christopher Han
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
#include "config/ConfigFactory.h"

const wxCmdLineEntryDesc cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, wxT("h"), wxT("help"), wxT("Display usage info"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
	{ wxCMD_LINE_SWITCH, wxT("V"), wxT("version"), wxT("Display version info") },
	{ wxCMD_LINE_SWITCH, wxT("v"), wxT("verbose"), wxT("Verbose execution") },
	{ wxCMD_LINE_NONE }
};

IMPLEMENT_APP(fbx::FBX)

bool fbx::FBX::OnInit()
{
	if (!ParseCmdLine())
		return false;
	engine = new FBXEngine();
	frame = new FBXFrame();
	frame->engine = engine;
	frame->Show(true);
	frame->OpenPlaylists(ConfigFactory::GetConfig().GetString("playlists",""));
	SetTopWindow(frame);
	SetExitOnFrameDelete(true);
	return true;
}

int fbx::FBX::OnExit()
{
	if (engine) {
		engine->Stop();
		delete engine;
	}
	ConfigFactory::Deallocate();
	return 0;
}

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
	verbose = cmd.Found(wxT("v"));
	return true;
}

bool fbx::FBX::GetVerbose() const
{
	return verbose;
}
