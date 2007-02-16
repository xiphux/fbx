/*
 * FBX.h
 * Core FBX definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBX_H
#define FBX_FBX_H

class wxApp;

namespace fbx
{

	class FBXFrame;
	class FBX: public wxApp
	{
	public:
		virtual bool OnInit();
		virtual int OnExit();
	protected:
		FBXFrame *frame;
	};

}

#endif /* FBX_FBX_H */
