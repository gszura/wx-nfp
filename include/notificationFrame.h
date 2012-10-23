/*******************************************************************************
//
// Name:        notificationFrame.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __NOTIFICATIONFRAME_h__
#define __NOTIFICATIONFRAME_h__

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
#include <wx/sizer.h>
#include "configClass.h"

#undef notificationFrame_STYLE
//#define notificationFrame_STYLE wxSTAY_ON_TOP | wxDIALOG_NO_PARENT
#define notificationFrame_STYLE wxFULL_REPAINT_ON_RESIZE

/******************************************************************************/

class notificationFrame : public wxDialog
{
private:
    DECLARE_EVENT_TABLE();
    configClass *m_config;
    bool m_hideOnClose;

public:
    notificationFrame(wxWindow *parent, configClass *config, const wxString& message, int textAlign = wxALIGN_LEFT, const wxPoint& pos = wxDefaultPosition, bool hideOnClose = false, const wxSize& size = wxDefaultSize, wxWindowID id = 1, const wxString &title = wxT("wx-nfp_notification"), long style = notificationFrame_STYLE);
    virtual ~notificationFrame();
    void setMessage(wxString);

private:
    wxButton *buttonClose;
    wxStaticText *text1;
    wxBoxSizer *sizer2;
    wxPanel *panel1;
    wxBoxSizer *sizer1;

private:
    enum {
        ID_buttonClose = 1001,
        ID_text1,
        ID_panel1,

        ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
    };

private:
    void OnClose(wxCloseEvent& event);
    void CreateGUIControls(const wxString& message, int textAlign);
    void buttonCloseClick (wxCommandEvent& event);
};

#endif
