/*
 * FBXFrame.h
 * FBX frame definition
 * Copyright (C) 2007 Christopher Han
 */
#ifndef FBX_FBXFRAME_H
#define FBX_FBXFRAME_H

namespace fbx
{

	class FBXFrame: public wxFrame
	{
	public:
		FBXFrame();
		void OnQuit(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);
	private:
		DECLARE_EVENT_TABLE()
	};

	enum {
		FBX_frame_quit = 1,
		FBX_frame_about,
	};

}

#endif /* FBX_FBXFRAME_H */
