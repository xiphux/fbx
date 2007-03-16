/*
 * FBXFrame.cpp
 * FBX frame implementation
 * Copyright (C) 2007 Christopher Han
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/listbox.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/bitmap.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/aui/auibook.h>
#include <wx/app.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#endif

#include <iostream>

#include "FBXFrame.h"
#include "FBXEngine.h"
#include "playlist/PlaylistFactory.h"
#include "PlaylistPanel.h"
#include "config/ConfigFactory.h"

#include "icons/stop.xpm"
#include "icons/pause.xpm"
#include "icons/play.xpm"
#include "icons/prev.xpm"
#include "icons/next.xpm"

BEGIN_EVENT_TABLE(fbx::FBXFrame, wxFrame)
	EVT_MENU(FBX_frame_quit, fbx::FBXFrame::OnQuit)
	EVT_MENU(FBX_frame_about, fbx::FBXFrame::OnAbout)
	EVT_MENU(FBX_frame_stop, fbx::FBXFrame::OnStop)
	EVT_MENU(FBX_frame_pause, fbx::FBXFrame::OnPause)
	EVT_MENU(FBX_frame_play, fbx::FBXFrame::OnPlay)
	EVT_MENU(FBX_frame_prev, fbx::FBXFrame::OnPrev)
	EVT_MENU(FBX_frame_next, fbx::FBXFrame::OnNext)
	EVT_LISTBOX_DCLICK(FBX_frame_playlist, fbx::FBXFrame::OnPlaylistChoice)
	EVT_COMMAND_SCROLL(FBX_frame_progress, fbx::FBXFrame::OnSeek)
	EVT_IDLE(fbx::FBXFrame::OnIdle)
	EVT_TIMER(FBX_frame_timer, fbx::FBXFrame::OnTimer)
	EVT_CHOICE(FBX_frame_order, fbx::FBXFrame::OnOrder)
END_EVENT_TABLE()

fbx::FBXFrame::FBXFrame():
	wxFrame((wxFrame*)NULL, -1, wxEmptyString, wxDefaultPosition, wxSize(640,480)),
	timer(this,FBX_frame_timer),
	plidx(0)
{
	wxString ttl = wxT(PACKAGE_STRING);
	SetTitle(ttl);

	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *filemenu = new wxMenu;
	filemenu->Append(FBX_frame_quit, wxT("E&xit"));
	menubar->Append(filemenu, wxT("&File"));
	wxMenu *playmenu = new wxMenu;
	playmenu->Append(FBX_frame_stop, wxT("&Stop"));
	playmenu->Append(FBX_frame_pause, wxT("P&ause"));
	playmenu->Append(FBX_frame_play, wxT("P&lay"));
	playmenu->Append(FBX_frame_prev, wxT("P&rev"));
	playmenu->Append(FBX_frame_next, wxT("&Next"));
	menubar->Append(playmenu, wxT("&Playback"));
	wxMenu *helpmenu = new wxMenu;
	helpmenu->Append(FBX_frame_about, wxT("&About"));
	menubar->Append(helpmenu, wxT("&Help"));
	SetMenuBar(menubar);

	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	playbacktoolbar = CreateToolBar();
	wxBitmap stopbitmap(stop_xpm);
	playbacktoolbar->AddTool(FBX_frame_stop, wxT("Stop"), stopbitmap, wxT("Stop"));
	wxBitmap pausebitmap(pause_xpm);
	playbacktoolbar->AddTool(FBX_frame_pause, wxT("Pause"), pausebitmap, wxT("Pause"));
	wxBitmap playbitmap(play_xpm);
	playbacktoolbar->AddTool(FBX_frame_play, wxT("Play"), playbitmap, wxT("Play"));
	wxBitmap prevbitmap(prev_xpm);
	playbacktoolbar->AddTool(FBX_frame_prev, wxT("Previous"), prevbitmap, wxT("Previous"));
	wxBitmap nextbitmap(next_xpm);
	playbacktoolbar->AddTool(FBX_frame_next, wxT("Next"), nextbitmap, wxT("Next"));
	playbacktoolbar->AddSeparator();
	playbacktoolbar->AddControl(new wxStaticText(playbacktoolbar,-1,wxT("Order")));
	wxArrayString tmp;
	tmp.Add(wxT("Default"));
	tmp.Add(wxT("Random"));
	tmp.Add(wxT("Repeat (playlist)"));
	tmp.Add(wxT("Repeat (track)"));
	order = new wxChoice(playbacktoolbar,FBX_frame_order,wxDefaultPosition,wxDefaultSize,tmp);
	order->SetSelection(ConfigFactory::GetConfig().GetInt("order",0));
	playbacktoolbar->AddControl(order);
	playbacktoolbar->Realize();

	//progresstoolbar = CreateToolBar(wxTB_DOCKABLE);
	progress = new wxSlider(this,FBX_frame_progress,0,0,1);
	progress->Enable(false);
	topsizer->Add(progress, 0, wxEXPAND|wxALL);
	//progresstoolbar->AddControl(progress);
	//progresstoolbar->Realize();

	notebook = new wxAuiNotebook(this);
	topsizer->Add(notebook, 1, wxEXPAND|wxALL);

	statusbar = CreateStatusBar();

	SetSizer(topsizer);

	SetExtraStyle(wxWS_EX_PROCESS_IDLE);
	wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
	timer.Start(500);
}

void fbx::FBXFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	if (engine)
		engine->Stop();
	Close(true);
}

void fbx::FBXFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString about = wxT(PACKAGE_STRING);
	about += wxT("\nCopyright (C) 2007 Christopher Han");
	wxMessageBox(about, wxT("About FBX"), wxOK|wxICON_INFORMATION);
}

void fbx::FBXFrame::OpenPlaylists(std::string pls)
{
	std::string::size_type lastpos = pls.find_first_not_of(",",0);
	std::string::size_type pos = pls.find_first_of(",",lastpos);
	while ((pos != std::string::npos) || (lastpos != std::string::npos)) {
		std::string pl = pls.substr(lastpos, pos - lastpos);
		if (PlaylistFactory::IsPlaylist(pl)) {
			std::string name = pls.substr(0,pls.find_last_of('.'));
			std::string::size_type tmp = name.find_last_of('/');
			if (tmp != std::string::npos)
				name = name.substr(tmp + 1);
			playlists[name] = pls;
		}
		lastpos = pls.find_first_not_of(",",pos);
		pos = pls.find_first_of(",",lastpos);
	}
	if (playlists.size() < 1)
		playlists["Default"] = "";
	for (std::map<std::string,std::string>::iterator iter = playlists.begin(); iter != playlists.end(); iter++)
		AddPlaylistPage(iter->first, iter->second);
}

void fbx::FBXFrame::AddPlaylistPage(std::string name, std::string file)
{
	wxString n(name.c_str(), *wxConvCurrent);
	notebook->AddPage(new PlaylistPanel(notebook,FBX_frame_playlist,file), n);
}

void fbx::FBXFrame::OnStop(wxCommandEvent& WXUNUSED(event))
{
	bool ret = engine->Stop();
#ifdef DEBUG
	std::cout << "FBXFrame::OnStop:" << (ret ? "true" : "false") << std::endl;
#endif
	ResetSlider();
}

void fbx::FBXFrame::OnPause(wxCommandEvent& WXUNUSED(event))
{
	bool ret = engine->Pause();
#ifdef DEBUG
	std::cout << "FBXFrame::OnPause:" << (ret ? "true" : "false") << std::endl;
#endif
}

void fbx::FBXFrame::OnPlay(wxCommandEvent& WXUNUSED(event))
{
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	bool ret = Play(page->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnPlay:" << (ret ? "true" : "false") << std::endl;
#endif
}

void fbx::FBXFrame::OnPrev(wxCommandEvent& WXUNUSED(event))
{
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	bool ret = page->Prev((order->GetCurrentSelection() == 1));
	if (order->GetCurrentSelection() == 2 && !ret) {
		page->SetActive(page->Size()-1);
		ret = true;
	}
	if (ret)
		Play(page->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnPrev" << std::endl;
#endif
}

void fbx::FBXFrame::OnNext(wxCommandEvent& WXUNUSED(event))
{
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	bool ret = page->Next((order->GetCurrentSelection() == 1));
	if (order->GetCurrentSelection() == 2 && !ret) {
		page->SetActive(0);
		ret = true;
	}
	if (ret)
		Play(page->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnNext" << std::endl;
#endif
}

void fbx::FBXFrame::OnIdle(wxIdleEvent& event)
{
	//event.RequestMore();
}

void fbx::FBXFrame::ResetSlider()
{
#ifdef DEBUG
	std::cout << "FBXFrame::ResetSlider" << std::endl;
#endif
	progress->SetValue(0);
	progress->SetRange(0,1);
	progress->Enable(false);
}

bool fbx::FBXFrame::Play(const std::string& file)
{
	//engine->Stop();
	bool ret = engine->Play(file);
	progress->Enable(true);
	progress->SetRange(0,engine->Size());
#ifdef DEBUG
	std::cout << "Range [0:" << engine->Size() << "]" << std::endl;
	std::cout << "Now Playing: " << engine->Metadata() << std::endl;
#endif
	return ret;
}

void fbx::FBXFrame::OnSeek(wxScrollEvent& event)
{
	bool ret = engine->Seek((double)event.GetPosition());
#ifdef DEBUG
	std::cout << "FBXFrame::OnSeek(" << event.GetPosition() << "): " << (ret ? "true" : "false") << std::endl;
#endif
}

void fbx::FBXFrame::OnPlaylistChoice(wxCommandEvent& event)
{
	int idx = event.GetSelection();
	char *str = (char*)event.GetClientData();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	page->SetActive(idx);
	Play(std::string(str));
}

bool fbx::FBXFrame::TryAdvance()
{
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	bool ret = true;
	if (order->GetCurrentSelection() != 3)
		ret = page->Next((order->GetCurrentSelection() == 1));
	if (order->GetCurrentSelection() == 2 && !ret) {
		page->SetActive(0);
		ret = true;
	}
	if (ret)
		return Play(page->Current());
	return false;
}

void fbx::FBXFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	//wxWakeUpIdle();
	UpdateStatus();
	if ((engine->Eof()/* || engine->Stopped()*/) && progress->IsEnabled()) {
		if (!TryAdvance()) {
			engine->Stop();
			ResetSlider();
		}
	}
}

void fbx::FBXFrame::UpdateStatus()
{
	std::string st = engine->StatusString();
	wxString s(st.c_str(), *wxConvCurrent);
	statusbar->SetStatusText(s);
	progress->SetValue(engine->Current());
}

void fbx::FBXFrame::OnOrder(wxCommandEvent& WXUNUSED(event))
{
	ConfigFactory::GetConfig().SetInt("order",order->GetCurrentSelection());
}
