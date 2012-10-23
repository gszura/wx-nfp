/*******************************************************************************
//
// Name:        customWindowTop.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __CUSTOM_WINDOW_TOP__
#define __CUSTOM_WINDOW_TOP__

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "configClass.h"
#include "drawingClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "cardFrame.h"


/******************************************************************************/

/**
 * windows to display the general card information
 */
class customWindowTop: public wxScrolledWindow {
     // VARIABLES
private:
     DECLARE_EVENT_TABLE()

     wxWindow *m_parent;
     cardFrame *m_cardFrm;
     configClass *m_config;
     cycleDataClass *m_cycleData;
     drawingClass *m_drawing;

public:

     // METHODS
public:
     customWindowTop(wxWindow *parent,
                     cardFrame *cardFrm,
                     configClass *config,
                     cycleDataClass *cycleData,
                     wxWindowID winid = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     long style = wxScrolledWindowStyle,
                     const wxString& name = wxPanelNameStr);

     void OnPaint(wxPaintEvent &event);
     void OnMouseDClick(wxMouseEvent &event);

     void recalculateComponentsSizes();

private:
     utilClass util;


};

/******************************************************************************/

#endif
