/*******************************************************************************
//
// Name:        customWindowMain.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __CUSTOM_WINDOW_MAIN__
#define __CUSTOM_WINDOW_MAIN__

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "configClass.h"
#include "drawingClass.h"
#include "customWindowLeft.h"
#include "customWindowNotes.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "dayFrame.h"

/******************************************************************************/

/**
 * windows to display cycle chart
 */
class customWindowMain: public wxScrolledWindow
{
    // VARIABLES
private:
    DECLARE_EVENT_TABLE()

    wxWindow *m_parent;
    customWindowLeft *m_windowLeft;
    dayFrame *m_dayFrm;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    drawingClass *m_drawing;
    wxScrolledWindow *m_notesWindow;

    int m_pixelsPerUnitX;
    int m_noUnitsX;

    int m_lastOpenedCard;
    int m_prevCommantedDay;
    int m_prevMarkedDay;

    utilClass m_util;


public:
    enum {
        ID_NOTESWINDOW = 3001,
        ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
    };
    // METHODS
public:
    customWindowMain(wxWindow *parent, customWindowLeft *windowLeft, dayFrame *dayFrm, configClass *config, cycleDataClass *cycleData, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxScrolledWindowStyle, const wxString& name = wxPanelNameStr);

    void OnPaint(wxPaintEvent &event);
    void OnMouseClick(wxMouseEvent &event);
    void OnMouseDClick(wxMouseEvent &event);
    void OnMouseMotion(wxMouseEvent &event);

    void repaint(int id);
    void repaint_activeDayUpdated(bool);
    void repaint_activeDayChanged();
    void repaint_daysUpdated(int, int);

    int getCellWidth(int day);
    int getCellHeight();

private:
    void markDayAndRow(wxDC &dc, int dayNo, int rowNo);
};

/******************************************************************************/

#endif
