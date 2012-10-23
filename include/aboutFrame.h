/*******************************************************************************
//
// Name:        aboutFrame.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __ABOUT_FRAME__
#define __ABOUT_FRAME__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dialog.h>
#else
#include <wx/wxprec.h>
#endif

#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/hyperlink.h>

#include "nfpMainFrame.h"
#include "configClass.h"
#include "utilClass.h"

/******************************************************************************/
#undef aboutFrame_STYLE
#define aboutFrame_STYLE wxSTAY_ON_TOP | wxFRAME_TOOL_WINDOW

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class aboutFrame : public wxDialog {
private:
     DECLARE_EVENT_TABLE();
     configClass *m_config;
     int m_timeTics;
     utilClass m_util;
     nfpMainFrame* m_mainFrame;

public:
     aboutFrame(wxWindow *parent, wxString fileToOpen, configClass *config, wxWindowID id = 1, const wxString &title = wxT("NFP - about"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = aboutFrame_STYLE);
     virtual ~aboutFrame();

public:
     wxButton *buttonClose;
     wxButton *buttonUpdate;
     wxBoxSizer *WxBoxSizer4;
     wxStaticText *staticAppVersion;
     wxHyperlinkCtrl *staticHomeUrl;
     wxBoxSizer *WxBoxSizer3;
     wxStaticText *staticCycleObservationCard;
     wxStaticText *staticNfp;
     wxStaticBitmap *WxStaticBitmap1;
     wxBoxSizer *WxBoxSizer2;
     wxPanel *WxPanel1;
     wxBoxSizer *WxBoxSizer1;
     wxTimer *timer1;

public:
     enum {
          ID_BUTTONCLOSE = 1024,
          ID_BUTTONUPDATE = 1026,
          ID_STATIC_APP_VERSION = 1021,
          ID_STATIC_HOME_URL = 1022,
          ID_STATIC_COC = 1017,
          ID_STATIC_NFP = 1016,
          ID_WXSTATICBITMAP1 = 1019,
          ID_WXPANEL1 = 1010,
          ID_TIMER1 = 1100,
          ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
     };

public:
     void aboutFrameClose(wxCloseEvent& event);
     void CreateGUIControls(void);
     void buttonCloseClick(wxCommandEvent& event);
     void buttonUpdateClick(wxCommandEvent& event);
     void timer1Timer(wxTimerEvent& event);

     void setButtonsStyle();

};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif
