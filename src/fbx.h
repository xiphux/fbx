/*
 * fbx.h
 * Core FBX definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBX_H
#define FBX_FBX_H

class wxApp;
class wxLocale;

namespace fbx
{

	class fbx: public wxApp
	{
	public:
		virtual bool OnInit();
		virtual int OnExit();
	};

}

#endif /* FBX_FBX_H */
