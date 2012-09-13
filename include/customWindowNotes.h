/*******************************************************************************
//
// Name:        customWindowNotes.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __CUSTOM_WINDOW_NOTES__
#define __CUSTOM_WINDOW_NOTES__

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "configClass.h"
#include "utilClass.h"


/******************************************************************************/

/**
 * windows to display the additional notes (of card and day)
 */
class customWindowNotes: public wxScrolledWindow {
     // VARIABLES
private:
     DECLARE_EVENT_TABLE()

     wxWindow *m_parent;
     configClass *m_config;

public:

     // METHODS
public:
     customWindowNotes(wxWindow *parent,
                       configClass *config,
                       wxWindowID winid = wxID_ANY,
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxDefaultSize,
                       long style = wxScrolledWindowStyle,
                       const wxString& name = wxPanelNameStr);

     void OnPaint(wxPaintEvent &event);

private:
     utilClass util;

};

/******************************************************************************/

#endif
