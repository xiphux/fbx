/*
 * fbx.cpp
 * Core FBX implementation
 * Copyright (C) 2007 Christopher Han
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/app.h>
#include <wx/cmdline.h>
#endif

#include "fbx.h"

IMPLEMENT_APP(fbx::fbx)

bool fbx::fbx::OnInit()
{
	return true;
}

int fbx::fbx::OnExit()
{
	return 0;
}

