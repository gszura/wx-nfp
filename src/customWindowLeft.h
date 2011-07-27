/*******************************************************************************
//
// Name:        customWindowLeft.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __CUSTOM_WINDOW_LEFT__
#define __CUSTOM_WINDOW_LEFT__

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/button.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>

#include "configClass.h"
#include "drawingClass.h"
#include "cyclesData.h"
#include "utilClass.h"


/******************************************************************************/

/**
 * windows to display left column
 */
class customWindowLeft: public wxScrolledWindow {
    // VARIABLES
private:
    DECLARE_EVENT_TABLE()

    wxWindow *m_parent;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    drawingClass *m_drawing;
    int m_lastOpenedCard;
    utilClass m_util;
    int m_prevMarkedRow;

public:

    // METHODS
public:
    customWindowLeft(wxWindow *parent,
                     configClass *config,
                     cycleDataClass *cycleData,
                     wxWindowID winid = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     long style = wxScrolledWindowStyle,
                     const wxString& name = wxPanelNameStr);

    void OnPaint(wxPaintEvent &event);
    void OnMouseClick(wxMouseEvent &event);

    void repaint_activeCardUpdated();
    void recalculateComponentsSizes();
    void markRow(int rowNo);
};

/******************************************************************************/

#endif
