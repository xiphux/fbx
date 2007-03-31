/**
 * @file FBXFrame.cpp
 * @brief FBX frame implementation
 * @author Christopher Han
 *
 * Main FBX window frame implementation
 * Copyright (C) 2007
 * Licensed under the terms of the GNU GPL v2
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
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
#include <wx/filedlg.h>
#include <wx/aui/aui.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

#include "FBXFrame.h"
#include "FBXEngine.h"
#include "playlist/PlaylistFactory.h"
#include "PlaylistPanel.h"
#include "config/ConfigFactory.h"
#include "audiofile/AudioFileFactory.h"

#include "icons/stop.xpm"
#include "icons/pause.xpm"
#include "icons/play.xpm"
#include "icons/prev.xpm"
#include "icons/next.xpm"

/**
 * @brief GUI status bar update frequency
 */
#define GUIUPDATE 500

/**
 * Event handler table
 */
BEGIN_EVENT_TABLE(fbx::FBXFrame, wxFrame)
	EVT_MENU(FBX_frame_quit, fbx::FBXFrame::OnQuit)
	EVT_MENU(FBX_frame_about, fbx::FBXFrame::OnAbout)
	EVT_MENU(FBX_frame_stop, fbx::FBXFrame::OnStop)
	EVT_MENU(FBX_frame_pause, fbx::FBXFrame::OnPause)
	EVT_MENU(FBX_frame_play, fbx::FBXFrame::OnPlay)
	EVT_MENU(FBX_frame_prev, fbx::FBXFrame::OnPrev)
	EVT_MENU(FBX_frame_next, fbx::FBXFrame::OnNext)
	EVT_MENU(FBX_frame_addfiles, fbx::FBXFrame::OnAddFiles)
	EVT_MENU(FBX_frame_saveplaylist, fbx::FBXFrame::OnSavePlaylist)
	EVT_MENU(FBX_frame_remfile, fbx::FBXFrame::OnRemFile)
	EVT_MENU(FBX_frame_openplaylist, fbx::FBXFrame::OnOpenPlaylist)
	EVT_MENU(FBX_frame_closeplaylist, fbx::FBXFrame::OnClosePlaylist)
	EVT_MENU_OPEN(fbx::FBXFrame::OnMenuOpen)
	EVT_MENU_CLOSE(fbx::FBXFrame::OnMenuClose)
	EVT_CHOICE(FBX_frame_order, fbx::FBXFrame::OnOrder)
	EVT_LISTBOX_DCLICK(FBX_frame_playlist, fbx::FBXFrame::OnPlaylistChoice)
	EVT_COMMAND_SCROLL(FBX_frame_progress, fbx::FBXFrame::OnSeek)
	EVT_IDLE(fbx::FBXFrame::OnIdle)
	EVT_TIMER(FBX_frame_timer, fbx::FBXFrame::OnTimer)
END_EVENT_TABLE()

/**
 * Constructor
 */
fbx::FBXFrame::FBXFrame():
	wxFrame((wxFrame*)NULL, -1, wxEmptyString, wxDefaultPosition, wxSize(640,480)),
	plidx(0),
	updatestatus(true),
	firstplay(true)
{
	wxString ttl = wxT(PACKAGE_STRING);
	SetTitle(ttl);

	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *filemenu = new wxMenu;
	filemenu->Append(FBX_frame_addfiles, wxT("&Add files"), wxT("Add files to playlist"));
	filemenu->Append(FBX_frame_remfile, wxT("&Remove file"), wxT("Remove file from playlist"));
	filemenu->AppendSeparator();
	filemenu->Append(FBX_frame_openplaylist, wxT("&Open playlist"), wxT("Open playlist file"));
	filemenu->Append(FBX_frame_saveplaylist, wxT("&Save playlist"), wxT("Save playlist changes to file"));
	filemenu->Append(FBX_frame_closeplaylist, wxT("&Close playlist"), wxT("Close playlist"));
	filemenu->AppendSeparator();
	filemenu->Append(FBX_frame_quit, wxT("E&xit"), wxT("Exit FBX"));
	menubar->Append(filemenu, wxT("&File"));
	wxMenu *playmenu = new wxMenu;
	playmenu->Append(FBX_frame_stop, wxT("&Stop"), wxT("Stop"));
	playmenu->Append(FBX_frame_pause, wxT("P&ause"), wxT("Pause"));
	playmenu->Append(FBX_frame_play, wxT("P&lay"), wxT("Play"));
	playmenu->Append(FBX_frame_prev, wxT("P&rev"), wxT("Previous"));
	playmenu->Append(FBX_frame_next, wxT("&Next"), wxT("Next"));
	menubar->Append(playmenu, wxT("&Playback"));
	wxMenu *helpmenu = new wxMenu;
	helpmenu->Append(FBX_frame_about, wxT("&About"), wxT("About FBX"));
	menubar->Append(helpmenu, wxT("&Help"));
	SetMenuBar(menubar);

	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	toolbarpanel = new wxPanel(this,-1);
	topsizer->Add(toolbarpanel,0,wxEXPAND|wxALL);
	manager = new wxAuiManager(toolbarpanel, wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG );

	playbacktoolbar = new wxToolBar(toolbarpanel,-1);
	//playbacktoolbar = CreateToolBar();
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
	playbacktoolbar->Realize();
//	playbacktoolbar->AddSeparator();
//	playbacktoolbar->AddControl(new wxStaticText(playbacktoolbar,-1,wxT("Order")));
//	playbacktoolbar->AddControl(order);
	wxAuiPaneInfo pti;
	pti.CloseButton(false);
	pti.Top();
	pti.Resizable(false);
	pti.Gripper(true);
	pti.GripperTop(false);
	pti.MaxSize(128,20);
	pti.Caption(wxT("Playback"));
	pti.CaptionVisible(true);
	manager->AddPane(playbacktoolbar,pti);

	wxArrayString tmp;
	tmp.Add(wxT("Default"));
	tmp.Add(wxT("Random"));
	tmp.Add(wxT("Repeat (playlist)"));
	tmp.Add(wxT("Repeat (track)"));
	order = new wxChoice(playbacktoolbar,FBX_frame_order,wxDefaultPosition,wxDefaultSize,tmp);
	order->SetSelection(config::ConfigFactory::GetConfig().GetInt("order",0));
	pti.Caption(wxT("Order"));
	manager->AddPane(order,pti);

	//progresstoolbar = CreateToolBar(wxTB_DOCKABLE);
	progress = new wxSlider(this,FBX_frame_progress,0,0,1);
	progress->Enable(false);
	//topsizer->Add(progress, 0, wxEXPAND|wxALL);
	pti.Resizable(true);
	pti.MinSize(128,20);
	pti.Caption(wxT("Progress"));
	manager->AddPane(progress,pti);
	
	//progresstoolbar->AddControl(progress);
	//progresstoolbar->Realize();

	notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE & ~wxAUI_NB_CLOSE_ON_ACTIVE_TAB );
	topsizer->Add(notebook, 3, wxEXPAND|wxALL);

	statusbar = CreateStatusBar();

	SetSizer(topsizer);

	SetExtraStyle(wxWS_EX_PROCESS_IDLE);
	wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
	timer = new wxTimer(this,FBX_frame_timer);
	timer->Start(GUIUPDATE);
	manager->Update();
}

/**
 * Called when quit menu option is chosen
 */
void fbx::FBXFrame::OnQuit(wxCommandEvent& event)
{
	PlaylistPanel *page;
	size_t pagecount = notebook->GetPageCount();
	for (int i = 0; i < pagecount; i++) {
		page = (PlaylistPanel*)notebook->GetPage(i);
		if (!page->Saved()) {
			wxMessageDialog prompt(this, wxT("You have unsaved playlists.  Are you sure you want to quit?"), wxT("Unsaved playlists"), wxOK|wxCANCEL|wxICON_INFORMATION);
			if (prompt.ShowModal() == wxID_CANCEL)
				return;
		}
	}
	timer->Stop();
	if (engine)
		engine->Stop();
	manager->UnInit();

	bool first = true;
	std::string pls;
	pagecount = notebook->GetPageCount();
	for (int i = 0; i < pagecount; i++) {
		page = (PlaylistPanel*)notebook->GetPage(i);
		if (page) {
			if (!first)
				pls += ",";
			pls += page->GetFilename();
			first = false;
		}
	}
	config::ConfigFactory::GetConfig().SetString("playlists",pls);

	Close(true);
}

/**
 * Called when about menu option is chosen
 */
void fbx::FBXFrame::OnAbout(wxCommandEvent& event)
{
	wxString about = wxT(PACKAGE_STRING);
	about += wxT("\nCopyright (C) 2007 Christopher Han");
	wxMessageBox(about, wxT("About FBX"), wxOK|wxICON_INFORMATION);
}

/**
 * Opens a series of playlists given in a string
 */
void fbx::FBXFrame::OpenSavedPlaylists(std::string pls)
{
	bool empty = true;
	std::string::size_type lastpos = pls.find_first_not_of(",",0);
	std::string::size_type pos = pls.find_first_of(",",lastpos);
	while ((pos != std::string::npos) || (lastpos != std::string::npos)) {
		std::string pl = pls.substr(lastpos, pos - lastpos);
#ifdef DEBUG
		std::cout << "FBXFrame::OpenSavedPlaylists: \"" << pl << "\"" << std::endl;
#endif
		OpenPlaylist(pl);
		empty = false;
		lastpos = pls.find_first_not_of(",",pos);
		pos = pls.find_first_of(",",lastpos);
	}
	if (empty) {
		//playlists["Default"] = "";
		AddPlaylistPage("Default","");
	}
	activeplaylist = (PlaylistPanel*)notebook->GetPage(0);
}

/**
 * Opens a single playlist
 */
bool fbx::FBXFrame::OpenPlaylist(std::string pls)
{
	if (playlist::PlaylistFactory::IsPlaylist(pls)) {
		std::string name = pls.substr(0,pls.find_last_of('.'));
		std::string::size_type tmp = name.find_last_of('/');
		if (tmp != std::string::npos)
			name = name.substr(tmp + 1);
//			std::map<std::string,std::string>::iterator tp = playlists.find(name);
//			while (tp != playlists.end()) {
//				name += "(1)";
//				tp = playlists.find(name);
//			}
#ifdef DEBUG
		std::cout << "FBXFrame::OpenPlaylist: [ " << name << " : " << pls << " ] " << std::endl;
#endif
		playlists[name] = pls;
		AddPlaylistPage(name,pls);
		return true;
	}
	return false;
}

/**
 * Adds a page to the tabbed playlist interface with the given
 * name/file
 */
void fbx::FBXFrame::AddPlaylistPage(std::string name, std::string file)
{
#ifdef DEBUG
	std::cout << "FBXFrame::AddPlaylistPage: [ " << name << " : " << file << " ]" << std::endl;
#endif
	wxString n(name.c_str(), *wxConvCurrent);
	notebook->AddPage(new PlaylistPanel(notebook,FBX_frame_playlist,file), n);

}

/**
 * Called when stop button or menu option is chosen
 */
void fbx::FBXFrame::OnStop(wxCommandEvent& event)
{
	bool ret = Stop();
#ifdef DEBUG
	std::cout << "FBXFrame::OnStop:" << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when pause button or menu option is chosen
 */
void fbx::FBXFrame::OnPause(wxCommandEvent& event)
{
	if (engine->Stopped())
		return;
	updatestatus = !updatestatus;
	bool ret = engine->Pause();
#ifdef DEBUG
	std::cout << "FBXFrame::OnPause:" << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when play button or menu option is chosen
 */
void fbx::FBXFrame::OnPlay(wxCommandEvent& event)
{
	bool ret;
	if (!engine->Stopped() && engine->Paused()) {
		updatestatus = !updatestatus;
		ret = engine->Pause();
	} else {
		if (!engine->Stopped())
			return;
		if (order->GetCurrentSelection() == 1 && firstplay)
			activeplaylist->Next(true);
		ret = Play(activeplaylist->Current());
	}
#ifdef DEBUG
	std::cout << "FBXFrame::OnPlay:" << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when prev button or menu option is chosen
 */
void fbx::FBXFrame::OnPrev(wxCommandEvent& event)
{
	bool ret = activeplaylist->Prev((order->GetCurrentSelection() == 1));
	if (order->GetCurrentSelection() == 2 && !ret) {
		activeplaylist->SetActive(activeplaylist->Size()-1);
		ret = true;
	}
	if (ret && !engine->Stopped())
		Play(activeplaylist->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnPrev" << std::endl;
#endif
}

/**
 * Called when next button or menu option is chosen
 */
void fbx::FBXFrame::OnNext(wxCommandEvent& event)
{
	bool ret = activeplaylist->Next((order->GetCurrentSelection() == 1));
	if (order->GetCurrentSelection() == 2 && !ret) {
		activeplaylist->SetActive(0);
		ret = true;
	}
	if (ret && !engine->Stopped())
		Play(activeplaylist->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnNext" << std::endl;
#endif
}

/**
 * Called when GUI idles
 */
void fbx::FBXFrame::OnIdle(wxIdleEvent& event)
{
	//event.RequestMore();
}

/**
 * Resets seek bar position and disables it (when stopping playback)
 */
void fbx::FBXFrame::ResetSlider()
{
#ifdef DEBUG
	std::cout << "FBXFrame::ResetSlider" << std::endl;
#endif
	progress->SetValue(0);
	progress->SetRange(0,1);
	progress->Enable(false);
}

/**
 * Forwards play command to running audio engine
 */
bool fbx::FBXFrame::Play(const std::string& file)
{
	//engine->Stop();
	bool ret = engine->Play(file);
	updatestatus = true;
	firstplay = false;
	progress->Enable(true);
	progress->SetRange(0,engine->Size());
#ifdef DEBUG
	std::cout << "Range [0:" << engine->Size() << "]" << std::endl;
	std::string tmp = engine->Metadata();
	std::cout << "Now Playing: ";
	if (tmp.length() > 3)
		std::cout << engine->Metadata();
	else
		std::cout << file;
	std::cout << std::endl;
#endif
	return ret;
}

/**
 * Called when seek bar position is moved
 */
void fbx::FBXFrame::OnSeek(wxScrollEvent& event)
{
	bool ret = engine->Seek((double)event.GetPosition());
#ifdef DEBUG
	std::cout << "FBXFrame::OnSeek(" << event.GetPosition() << "): " << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when double-clicking an entry in the playlist
 */
void fbx::FBXFrame::OnPlaylistChoice(wxCommandEvent& event)
{
	int idx = event.GetSelection();
	char *str = (char*)event.GetClientData();
	activeplaylist = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	activeplaylist->SetActive(idx);
	Play(std::string(str));
}

/**
 * Attempts to advance playlist to next song
 */
bool fbx::FBXFrame::TryAdvance()
{
	bool ret = true;
	if (order->GetCurrentSelection() != 3)
		ret = activeplaylist->Next((order->GetCurrentSelection() == 1));
	if (!ret) {
		activeplaylist->SetActive(0);
		if (order->GetCurrentSelection() == 2)
			ret = true;
	}
	if (ret)
		return Play(activeplaylist->Current());
	return false;
}

/**
 * Called when update timer fires
 */
void fbx::FBXFrame::OnTimer(wxTimerEvent& event)
{
	//wxWakeUpIdle();
	if (updatestatus)
		UpdateStatus();
	if ((engine->Eof()/* || engine->Stopped()*/) && progress->IsEnabled()) {
		if (!TryAdvance())
			Stop();
	}
}

/**
 * Updates status bar information
 */
void fbx::FBXFrame::UpdateStatus()
{
	std::string st = engine->StatusString();
	wxString s(st.c_str(), *wxConvCurrent);
	int pg = notebook->GetPageIndex(activeplaylist);
	if (pg != wxNOT_FOUND)
		s += wxT(" | ") + notebook->GetPageText(pg);
	statusbar->SetStatusText(s);
	progress->SetValue(engine->Current());
}

/**
 * Called when changing the order setting in the toolbar
 */
void fbx::FBXFrame::OnOrder(wxCommandEvent& event)
{
	config::ConfigFactory::GetConfig().SetInt("order",order->GetCurrentSelection());
}

/**
 * Called when Add Files menu option is chosen
 */
void fbx::FBXFrame::OnAddFiles(wxCommandEvent& event)
{
	std::string ext = "Audio files|";
	ext += audiofile::AudioFileFactory::Extensions();
	ext += "|All files|*.*";
	wxString e(ext.c_str(), *wxConvCurrent);
	wxFileDialog dlg(this,wxT("Add files"),wxT(""),wxT(""),e,wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK) {
		int idx = notebook->GetSelection();
		PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
		wxArrayString ret;
		dlg.GetPaths(ret);
		size_t count = ret.GetCount();
		bool added = false;
		for (int i = 0; i < count; i++) {
#ifdef DEBUG
			std::cout << "Item " << i << ": " << ret[i].mb_str() << std::endl;
#endif
			std::string tmp(ret[i].mb_str());
			page->Add(tmp,true);
			added = true;
		}
		if (added) {
			wxString l = notebook->GetPageText(idx);
			size_t len = l.Len();
			if (l.GetChar(len-1) != '*') {
				l += wxT("*");
				notebook->SetPageText(idx,l);
			}
		}
	}
}

/**
 * Called when Save playlist menu option is chosen
 */
void fbx::FBXFrame::OnSavePlaylist(wxCommandEvent& event)
{
	int idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	bool ret = page->Save();
	if (ret) {
		wxString l = notebook->GetPageText(idx);
		size_t len = l.Len();
		if (l.GetChar(len-1) == '*') {
			l = l.Left(len-1);
			notebook->SetPageText(idx,l);
		}
	}
#ifdef DEBUG
	std::cout << "FBXFrame::OnSavePlaylist: " << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when Remove file menu option is chosen
 */
void fbx::FBXFrame::OnRemFile(wxCommandEvent& event)
{
	int idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	unsigned int selected = page->SelectedIdx();
	while (selected == page->CurrentIdx()) {
		bool ret = true;
		if (order->GetCurrentSelection() != 3)
			ret = page->Next((order->GetCurrentSelection() == 1));
		if (!ret) {
			page->SetActive(0);
			if (order->GetCurrentSelection() != 2)
				Stop();
		}
		if (progress->IsEnabled())
			Play(page->Current());
	}
	bool r = page->Remove(selected);
	if (r) {
		wxString l = notebook->GetPageText(idx);
		size_t len = l.Len();
		if (l.GetChar(len-1) != '*') {
			l += wxT("*");
			notebook->SetPageText(idx,l);
		}
	}
#ifdef DEBUG
	std::cout << "FBXFrame::OnRemFile: " << (r ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when Open playlist menu option is chosen
 */
void fbx::FBXFrame::OnOpenPlaylist(wxCommandEvent& event)
{
	std::string ext = "Playlists|";
	ext += playlist::PlaylistFactory::Extensions();
	ext += "|All files|*.*";
	wxString e(ext.c_str(), *wxConvCurrent);
	wxFileDialog dlg(this,wxT("Open playlist"),wxT(""),wxT(""),e,wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK) {
		std::string pl(dlg.GetPath().mb_str());
		OpenPlaylist(pl);
	}
}

/**
 * Called when a menu is opened
 */
void fbx::FBXFrame::OnOpenMenu(wxMenuEvent& event)
{
	updatestatus = false;
	statusbar->SetStatusText(wxT(""));
}

/**
 * Called when a menu is closed
 */
void fbx::FBXFrame::OnCloseMenu(wxMenuEvent& event)
{
	updatestatus = true;
}

/**
 * Forwards stop command to audio engine and resets GUI
 */
bool fbx::FBXFrame::Stop()
{
	bool ret = engine->Stop();
	updatestatus = false;
	ResetSlider();
	UpdateStatus();
	return ret;
}

/**
 * Called when Close playlist menu option is chosen
 */
void fbx::FBXFrame::OnClosePlaylist(wxCommandEvent& event)
{
	size_t idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	notebook->DeletePage(idx);
	if (page == activeplaylist) {
		size_t sz = notebook->GetPageCount();
		if (sz > 0) {
			if (idx > 0)
				idx--;
			activeplaylist = (PlaylistPanel*)notebook->GetPage(idx);
		} else {
			AddPlaylistPage("Default","");
			activeplaylist = (PlaylistPanel*)notebook->GetPage(0);
		}
	}
}
