/*******************************************************************************
//
// Name:        updatesNotificationForm.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __UPDATES_NOTIFICATION_FORM_h__
#define __UPDATES_NOTIFICATION_FORM_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif

#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/timer.h>
#include <wx/gauge.h>

#include "configClass.h"
#include "utilClass.h"
#include "liveUpdateClass.h"

#undef updatesNotificationForm_STYLE
#define updatesNotificationForm_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX

/******************************************************************************/

class updatesNotificationForm : public wxFrame {
private:
     DECLARE_EVENT_TABLE();

     wxWindow *m_parent;
     configClass *m_config;
     wxString m_newAppSetupFileUrl;
     liveUpdateClass *m_checkUpdatesThread;



public:
     updatesNotificationForm(wxWindow *parent, configClass *config, wxString newAppSetupFileUrl, wxWindowID id = 1, const wxString &title = wxT("NFP - New version is available"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = updatesNotificationForm_STYLE);
     virtual ~updatesNotificationForm();

public:
     wxTimer *timerUpdates;
     wxButton *buttonLater;
     wxButton *buttonInstall;
     wxBoxSizer *WxBoxSizer3;
     wxGauge *gauge;
     wxStaticText *staticUpdateAvailable;
     wxBoxSizer *WxBoxSizer2;
     wxPanel *WxPanel1;
     wxBoxSizer *WxBoxSizer1;

public:
     enum {
          ID_TIMERUPDATES = 1020,
          ID_BUTTONLATER = 1018,
          ID_BUTTONINSTALL = 1017,
          ID_GAUGE = 1019,
          ID_STATICUPDATEAVAILABLE = 1013,
          ID_WXPANEL1 = 1002,
          ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
     };

public:
     void updatesNotificationFormClose(wxCloseEvent& event);
     void CreateGUIControls(void);
     void buttonInstallClick(wxCommandEvent& event);
     void buttonLaterClick(wxCommandEvent& event);
     void newAppDownloadedEvent( wxCommandEvent& event);
     void timerUpdatesTimer(wxTimerEvent& event);
};

#endif
