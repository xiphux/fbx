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
#include <wx/accel.h>

#ifdef AUI_TOOLBAR
#include <wx/aui/aui.h>
#endif

#endif

#ifdef DEBUG
#include <iostream>
#endif

#include <sstream>

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
 * @brief Default playback order
 */
#define FBX_ORDER_DEFAULT 0

/**
 * @brief Random playback order
 */
#define FBX_ORDER_RANDOM 1

/**
 * @brief Repeat playlist playback order
 */
#define FBX_ORDER_REPEAT_PLAYLIST 2

/**
 * @brief Repeat track playback order
 */
#define FBX_ORDER_REPEAT_TRACK 3

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
	EVT_MENU(FBX_frame_saveplaylistas, fbx::FBXFrame::OnSavePlaylistAs)
	EVT_MENU(FBX_frame_remfile, fbx::FBXFrame::OnRemFile)
	EVT_MENU(FBX_frame_openplaylist, fbx::FBXFrame::OnOpenPlaylist)
	EVT_MENU(FBX_frame_closeplaylist, fbx::FBXFrame::OnClosePlaylist)
	EVT_MENU(FBX_frame_newplaylist, fbx::FBXFrame::OnNewPlaylist)
	EVT_MENU(FBX_frame_moveup, fbx::FBXFrame::OnMoveUp)
	EVT_MENU(FBX_frame_movedown, fbx::FBXFrame::OnMoveDown)
	EVT_MENU(FBX_frame_order_default, fbx::FBXFrame::OnOrderDefault)
	EVT_MENU(FBX_frame_order_random, fbx::FBXFrame::OnOrderRandom)
	EVT_MENU(FBX_frame_order_repeat_playlist, fbx::FBXFrame::OnOrderRepeatPlaylist)
	EVT_MENU(FBX_frame_order_repeat_track, fbx::FBXFrame::OnOrderRepeatTrack)
	EVT_MENU(FBX_frame_stop_after_current, fbx::FBXFrame::OnStopAfterCurrent)
	EVT_MENU_OPEN(fbx::FBXFrame::OnMenuOpen)
	EVT_MENU_CLOSE(fbx::FBXFrame::OnMenuClose)
	EVT_CHOICE(FBX_frame_order, fbx::FBXFrame::OnOrder)
	EVT_LISTBOX_DCLICK(FBX_frame_playlist, fbx::FBXFrame::OnPlaylistChoice)
	EVT_COMMAND_SCROLL_THUMBTRACK(FBX_frame_progress, fbx::FBXFrame::OnSeekStart)
	EVT_COMMAND_SCROLL_CHANGED(FBX_frame_progress, fbx::FBXFrame::OnSeek)
	EVT_TIMER(FBX_frame_timer, fbx::FBXFrame::OnTimer)
END_EVENT_TABLE()

/**
 * Constructor
 */
fbx::FBXFrame::FBXFrame():
	wxFrame((wxFrame*)NULL, -1, wxEmptyString, wxDefaultPosition, wxSize(640,480)),
	updatestatus(true),
	firstplay(true),
	stopaftercurrent(false),
	updateslider(true)
{
	wxString ttl = wxT(PACKAGE_STRING);
	SetTitle(ttl);

	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *filemenu = new wxMenu;
	filemenu->Append(FBX_frame_addfiles, wxT("&Add files"), wxT("Add files to playlist"));
	filemenu->Append(FBX_frame_remfile, wxT("&Remove file\tDel"), wxT("Remove file from playlist"));
	filemenu->Append(FBX_frame_moveup, wxT("Move &up\tShift+Up"), wxT("Move track up"));
	filemenu->Append(FBX_frame_movedown, wxT("Move &down\tShift+Down"), wxT("Move track down"));
	filemenu->AppendSeparator();
	filemenu->Append(FBX_frame_newplaylist, wxT("&New playlist"), wxT("Create new playlist"));
	filemenu->Append(FBX_frame_openplaylist, wxT("&Open playlist"), wxT("Open playlist file"));
	filemenu->Append(FBX_frame_saveplaylist, wxT("&Save playlist"), wxT("Save playlist changes"));
	filemenu->Append(FBX_frame_saveplaylistas, wxT("Sa&ve playlist as..."), wxT("Save playlist to specific file"));
	filemenu->Append(FBX_frame_closeplaylist, wxT("&Close playlist"), wxT("Close playlist"));
	filemenu->AppendSeparator();
	filemenu->Append(FBX_frame_quit, wxT("E&xit"), wxT("Exit FBX"));
	menubar->Append(filemenu, wxT("&File"));
	playmenu = new wxMenu;
	playmenu->Append(FBX_frame_stop, wxT("&Stop\tZ"), wxT("Stop"));
	playmenu->Append(FBX_frame_pause, wxT("P&ause\tX"), wxT("Pause"));
	playmenu->Append(FBX_frame_play, wxT("P&lay\tC"), wxT("Play"));
	playmenu->Append(FBX_frame_prev, wxT("P&rev\tShift+V"), wxT("Previous"));
	playmenu->Append(FBX_frame_next, wxT("&Next\tV"), wxT("Next"));
	playmenu->AppendSeparator();

	ordermenu = new wxMenu;

	ordermenu->AppendRadioItem(FBX_frame_order_default, wxT("Default"), wxT("Default order"));
	ordermenu->AppendRadioItem(FBX_frame_order_random, wxT("Random"), wxT("Random order"));
	ordermenu->AppendRadioItem(FBX_frame_order_repeat_playlist, wxT("Repeat (playlist)"), wxT("Repeat (playlist) order"));
	ordermenu->AppendRadioItem(FBX_frame_order_repeat_track, wxT("Repeat (track)"), wxT("Repeat (track) order"));
	playmenu->AppendSubMenu(ordermenu, wxT("Order"), wxT("Playback order"));
	
	playmenu->AppendCheckItem(FBX_frame_stop_after_current, wxT("Stop after Current"), wxT("Stop playback after current track"));

	menubar->Append(playmenu, wxT("&Playback"));
	wxMenu *helpmenu = new wxMenu;
	helpmenu->Append(FBX_frame_about, wxT("&About"), wxT("About FBX"));
	menubar->Append(helpmenu, wxT("&Help"));
	SetMenuBar(menubar);

	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	toolbarpanel = new wxPanel(this,-1);
	topsizer->Add(toolbarpanel,0,wxEXPAND|wxALL);

	playorder = config::ConfigFactory::GetConfig().GetInt("order",FBX_ORDER_DEFAULT);
	switch (playorder) {
		case FBX_ORDER_DEFAULT:
			ordermenu->Check(FBX_frame_order_default, true);
			break;
		case FBX_ORDER_RANDOM:
			ordermenu->Check(FBX_frame_order_random, true);
			break;
		case FBX_ORDER_REPEAT_PLAYLIST:
			ordermenu->Check(FBX_frame_order_repeat_playlist, true);
			break;
		case FBX_ORDER_REPEAT_TRACK:
			ordermenu->Check(FBX_frame_order_repeat_track, true);
			break;
	}
	InitToolbars();

	notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE & ~wxAUI_NB_CLOSE_ON_ACTIVE_TAB );
	topsizer->Add(notebook, 3, wxEXPAND|wxALL);

	statusbar = CreateStatusBar();

	SetSizer(topsizer);

	wxAcceleratorEntry entries[8];
	entries[0].Set(wxACCEL_NORMAL, (int) 'Z', FBX_frame_stop);
	entries[1].Set(wxACCEL_NORMAL, (int) 'X', FBX_frame_pause);
	entries[2].Set(wxACCEL_NORMAL, (int) 'C', FBX_frame_play);
	entries[3].Set(wxACCEL_SHIFT, (int) 'V', FBX_frame_prev);
	entries[4].Set(wxACCEL_NORMAL, (int) 'V', FBX_frame_next);
	entries[5].Set(wxACCEL_NORMAL, WXK_DELETE, FBX_frame_remfile);
	entries[6].Set(wxACCEL_SHIFT, WXK_UP, FBX_frame_moveup);
	entries[7].Set(wxACCEL_SHIFT, WXK_DOWN, FBX_frame_movedown);
	wxAcceleratorTable accel(8, entries);
	SetAcceleratorTable(accel);

	timer = new wxTimer(this,FBX_frame_timer);
	timer->Start(GUIUPDATE);
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
			wxMessageDialog prompt(this, wxT("You have unsaved playlists.  Are you sure you want to quit?"), wxT("Unsaved playlists"), wxYES_NO|wxNO_DEFAULT|wxICON_INFORMATION);
			if (prompt.ShowModal() == wxID_NO)
				return;
		}
	}
	timer->Stop();
	if (engine)
		engine->Stop();

#ifdef AUI_TOOLBAR
	manager->UnInit();
#endif

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
	if (empty)
		AddPlaylistPage(UniquePlaylistName("Default"),"");
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
			name = UniquePlaylistName(name.substr(tmp + 1));
#ifdef DEBUG
		std::cout << "FBXFrame::OpenPlaylist: [ " << name << " : " << pls << " ] " << std::endl;
#endif
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
		activeplaylist = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
		if (playorder == FBX_ORDER_RANDOM && firstplay)
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
	bool ret = activeplaylist->Prev((playorder == FBX_ORDER_RANDOM));
	if (playorder == FBX_ORDER_REPEAT_PLAYLIST && !ret) {
		activeplaylist->SetActive(activeplaylist->Size()-1, true);
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
	bool ret = activeplaylist->Next((playorder == FBX_ORDER_RANDOM));
	if (playorder == FBX_ORDER_REPEAT_PLAYLIST && !ret) {
		activeplaylist->SetActive(0, true);
		ret = true;
	}
	if (ret && !engine->Stopped())
		Play(activeplaylist->Current());
#ifdef DEBUG
	std::cout << "FBXFrame::OnNext" << std::endl;
#endif
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
 * Called when seek bar position is set
 */
void fbx::FBXFrame::OnSeek(wxScrollEvent& event)
{
	bool ret = engine->Seek((double)event.GetPosition());
	updateslider = true;
#ifdef DEBUG
	std::cout << "FBXFrame::OnSeek(" << event.GetPosition() << "): " << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when seek bar starts dragging
 */
void fbx::FBXFrame::OnSeekStart(wxScrollEvent& event)
{
	updateslider = false;
}

/**
 * Called when double-clicking an entry in the playlist
 */
void fbx::FBXFrame::OnPlaylistChoice(wxCommandEvent& event)
{
	int idx = event.GetSelection();
	char *str = (char*)event.GetClientData();
	activeplaylist = (PlaylistPanel*)notebook->GetPage(notebook->GetSelection());
	activeplaylist->SetActive(idx, false);
	Play(std::string(str));
}

/**
 * Attempts to advance playlist to next song
 */
bool fbx::FBXFrame::TryAdvance()
{
	if (stopaftercurrent)
		return false;
	bool ret = true;
	if (playorder != FBX_ORDER_REPEAT_TRACK)
		ret = activeplaylist->Next((playorder == FBX_ORDER_RANDOM));
	if (!ret) {
		activeplaylist->SetActive(0, true);
		if (playorder == FBX_ORDER_REPEAT_PLAYLIST)
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
	if (updateslider)
		progress->SetValue(engine->Current());
}

/**
 * Called when changing the order setting in the toolbar
 */
void fbx::FBXFrame::OnOrder(wxCommandEvent& event)
{
	playorder = order->GetCurrentSelection();
	config::ConfigFactory::GetConfig().SetInt("order",playorder);
	switch (playorder) {
		case FBX_ORDER_DEFAULT:
			ordermenu->Check(FBX_frame_order_default, true);
			break;
		case FBX_ORDER_RANDOM:
			ordermenu->Check(FBX_frame_order_random, true);
			break;
		case FBX_ORDER_REPEAT_PLAYLIST:
			ordermenu->Check(FBX_frame_order_repeat_playlist, true);
			break;
		case FBX_ORDER_REPEAT_TRACK:
			ordermenu->Check(FBX_frame_order_repeat_track, true);
			break;
	}
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
		if (added)
			AddStar(idx);
	}
}

/**
 * Called when Save playlist menu option is chosen
 */
void fbx::FBXFrame::OnSavePlaylist(wxCommandEvent& event)
{
	int idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	if (page->GetFilename().length() < 1) {
		OnSavePlaylistAs(event);
		return;
	}
	bool ret = page->Save();
	if (ret)
		RemoveStar(idx);
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
		if (playorder != FBX_ORDER_REPEAT_TRACK)
			ret = page->Next((playorder == FBX_ORDER_RANDOM));
		if (!ret) {
			page->SetActive(0, false);
			if (playorder != FBX_ORDER_REPEAT_PLAYLIST)
				Stop();
		}
		if (progress->IsEnabled())
			Play(page->Current());
	}
	bool r = page->Remove(selected);
	if (r)
		AddStar(idx);
#ifdef DEBUG
	std::cout << "FBXFrame::OnRemFile: " << (r ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when Open playlist menu option is chosen
 */
void fbx::FBXFrame::OnOpenPlaylist(wxCommandEvent& event)
{
	std::string ext = playlist::PlaylistFactory::Extensions();
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
	stopaftercurrent = false;
	playmenu->Check(FBX_frame_stop_after_current, false);
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
	if (!page->Saved()) {
		wxString n = notebook->GetPageText(idx);
		size_t len = n.Len();
		if (n.GetChar(len-1) == '*')
			n = n.Left(len-1);
		wxString str = wxT("Playlist \"") + n + wxT("\"");
		std::string fname = page->GetFilename();
		if (fname.length() > 0) {
			wxString f(fname.c_str(), *wxConvCurrent);
			str += wxT(" [") + f + wxT("]");
		}
		str += wxT(" is unsaved.  Are you sure you want to close?");
		wxMessageDialog prompt(this,str, wxT("Unsaved playlist"), wxYES_NO|wxNO_DEFAULT|wxICON_INFORMATION);
		if (prompt.ShowModal() == wxID_NO)
			return;
	}
	notebook->DeletePage(idx);
	if (page == activeplaylist) {
		Stop();
		size_t sz = notebook->GetPageCount();
		if (sz > 0) {
			if (idx > 0)
				idx--;
			activeplaylist = (PlaylistPanel*)notebook->GetPage(idx);
		} else {
			AddPlaylistPage(UniquePlaylistName("Default"),"");
			activeplaylist = (PlaylistPanel*)notebook->GetPage(0);
		}
	}
}

/**
 * Given a playlist name, attempt to append to it to make its name unique
 */
std::string fbx::FBXFrame::UniquePlaylistName(const std::string name)
{
	std::stringstream tname;
	tname << name;
	wxString n(name.c_str(), *wxConvCurrent);
	int idx = 0;
	int pagecount = notebook->GetPageCount();
	bool found = false;
	for (int i = 0; i < pagecount; i++) {
		wxString l = notebook->GetPageText(i);
		if (n == l) {
			found = true;
			break;
		}
	}
	while (found) {
		found = false;
		wxString n2 = n;
		n2 << wxT("(") << ++idx << wxT(")");
		for (int i = 0; i < pagecount; i++) {
			wxString l = notebook->GetPageText(i);
			if (n2 == l) {
				found = true;
				break;
			}
		}
	}
	if (idx > 0)
		tname << "(" << idx << ")";
	return tname.str();
}

/**
 * Called when New playlist menu option is chosen
 */
void fbx::FBXFrame::OnNewPlaylist(wxCommandEvent& event)
{
	AddPlaylistPage(UniquePlaylistName("New Playlist"),"");
}

/**
 * Called when Save playlist as menu option is chosen
 */
void fbx::FBXFrame::OnSavePlaylistAs(wxCommandEvent& event)
{
	std::string ext = playlist::PlaylistFactory::Extensions();
	ext += "|All files|*.*";
	wxString e(ext.c_str(), *wxConvCurrent);
	wxFileDialog dlg(this,wxT("Save playlist as"),wxT(""),wxT(""),e,wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_OK) {
#ifdef DEBUG
		std::cout << "FBXFrame::OnSavePlaylistAs: " << dlg.GetPath().mb_str() << std::endl;
#endif
		std::string pl(dlg.GetPath().mb_str());
		if (!playlist::PlaylistFactory::IsPlaylist(pl)) {
			wxMessageBox(wxT("Playlist does not end in a recognized extension"),wxT("Unrecognized playlist type"), wxOK|wxICON_ERROR);
			return;
		}
		int idx = notebook->GetSelection();
		PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
		bool ret = page->SetFilename(pl);
#ifdef DEBUG
		std::cout << "FBXFrame::OnSavePlaylistAs:SetFilename: " << (ret ? "true" : "false") << std::endl;
#endif
		ret = page->Save();
#ifdef DEBUG
		std::cout << "FBXFrame::OnSavePlaylistAs:Save: " << (ret ? "true" : "false") << std::endl;
#endif
		if (ret) {
			std::string name = pl.substr(0,pl.find_last_of('.'));
			std::string::size_type tmp = name.find_last_of('/');
			if (tmp != std::string::npos)
				name = UniquePlaylistName(name.substr(tmp + 1));
			wxString n(name.c_str(), *wxConvCurrent);
			notebook->SetPageText(idx,n);
		}
	}
}

/**
 * Called when Move Up menu option is chosen
 */
void fbx::FBXFrame::OnMoveUp(wxCommandEvent& event)
{
	size_t idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	bool ret = page->MoveUp(page->SelectedIdx());
	if (ret)
		AddStar(idx);
#ifdef DEBUG
	std::cout << "FBXFrame::OnMoveUp: " << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Called when Move Down menu option is chosen
 */
void fbx::FBXFrame::OnMoveDown(wxCommandEvent& event)
{
	size_t idx = notebook->GetSelection();
	PlaylistPanel *page = (PlaylistPanel*)notebook->GetPage(idx);
	bool ret = page->MoveDown(page->SelectedIdx());
	if (ret)
		AddStar(idx);
#ifdef DEBUG
	std::cout << "FBXFrame::OnMoveDown: " << (ret ? "true" : "false") << std::endl;
#endif
}

/**
 * Adds a star to a notebook page's name if one is not there already
 */
void fbx::FBXFrame::AddStar(const unsigned int i)
{
	wxString l = notebook->GetPageText(i);
	size_t len = l.Len();
	if (l.GetChar(len-1) != '*') {
		l += wxT("*");
		notebook->SetPageText(i,l);
	}
}

/**
 * Removes a star from a notebook's page name if one is not there already
 */
void fbx::FBXFrame::RemoveStar(const unsigned int i)
{
	wxString l = notebook->GetPageText(i);
	size_t len = l.Len();
	if (l.GetChar(len-1) == '*') {
		l = l.Left(len-1);
		notebook->SetPageText(i,l);
	}
}

/**
 * Creates toolbar panels
 */
void fbx::FBXFrame::InitToolbars()
{
#ifdef AUI_TOOLBAR

	manager = new wxAuiManager(toolbarpanel, wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG );

	playbacktoolbar = new wxToolBar(toolbarpanel,-1);
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
	order->SetSelection(playorder);
	pti.Caption(wxT("Order"));
	manager->AddPane(order,pti);

	progress = new wxSlider(this,FBX_frame_progress,0,0,1);
	progress->Enable(false);
	pti.Resizable(true);
	pti.MinSize(128,20);
	pti.Caption(wxT("Progress"));
	manager->AddPane(progress,pti);
	
	manager->Update();

#else

	wxBoxSizer *toolbarsizer = new wxBoxSizer(wxHORIZONTAL);

	playbacktoolbar = new wxToolBar(toolbarpanel,-1);
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
	toolbarsizer->Add(playbacktoolbar,0,wxEXPAND|wxALL);

	toolbarsizer->AddSpacer(10);

	wxStaticText *orderlabel = new wxStaticText(toolbarpanel,-1,wxT("Order"));
	toolbarsizer->Add(orderlabel,0,wxALIGN_CENTER_VERTICAL);

	wxArrayString tmp;
	tmp.Add(wxT("Default"));
	tmp.Add(wxT("Random"));
	tmp.Add(wxT("Repeat (playlist)"));
	tmp.Add(wxT("Repeat (track)"));
	order = new wxChoice(toolbarpanel,FBX_frame_order,wxDefaultPosition,wxDefaultSize,tmp);
	order->SetSelection(playorder);
	toolbarsizer->Add(order,0,wxEXPAND|wxALL);

	toolbarsizer->AddSpacer(10);

	progress = new wxSlider(toolbarpanel,FBX_frame_progress,0,0,1);
	progress->Enable(false);
	toolbarsizer->Add(progress,1,wxEXPAND|wxALL);
	
	toolbarpanel->SetSizer(toolbarsizer);

#endif
}

/**
 * Called when Default order is chosen
 */
void fbx::FBXFrame::OnOrderDefault(wxCommandEvent& event)
{
	playorder = FBX_ORDER_DEFAULT;
	config::ConfigFactory::GetConfig().SetInt("order",playorder);
	order->SetSelection(playorder);
}

/**
 * Called when Random order is chosen
 */
void fbx::FBXFrame::OnOrderRandom(wxCommandEvent& event)
{
	playorder = FBX_ORDER_RANDOM;
	config::ConfigFactory::GetConfig().SetInt("order",playorder);
	order->SetSelection(playorder);
}

/**
 * Called when Repeat (playlist) order is chosen
 */
void fbx::FBXFrame::OnOrderRepeatPlaylist(wxCommandEvent& event)
{
	playorder = FBX_ORDER_REPEAT_PLAYLIST;
	config::ConfigFactory::GetConfig().SetInt("order",playorder);
	order->SetSelection(playorder);
}

/**
 * Called when Repeat (track) order is chosen
 */
void fbx::FBXFrame::OnOrderRepeatTrack(wxCommandEvent& event)
{
	playorder = FBX_ORDER_REPEAT_TRACK;
	config::ConfigFactory::GetConfig().SetInt("order",playorder);
	order->SetSelection(playorder);
}

/**
 * Called when "Stop after Current" is checked or unchecked
 */
void fbx::FBXFrame::OnStopAfterCurrent(wxCommandEvent& event)
{
	stopaftercurrent = playmenu->IsChecked(FBX_frame_stop_after_current);
}
