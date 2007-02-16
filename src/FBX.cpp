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
#endif

#include "FBX.h"
#include "FBXFrame.h"

IMPLEMENT_APP(fbx::FBX)

bool fbx::FBX::OnInit()
{
	frame = new FBXFrame();
	frame->Show(true);
	SetTopWindow(frame);
	SetExitOnFrameDelete(true);
	return true;
}

int fbx::FBX::OnExit()
{
	return 0;
}

