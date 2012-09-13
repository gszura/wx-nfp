/*******************************************************************************
//
// Name:        customChartWindow.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef CUSTOMCHARTWINDOW_H
#define CUSTOMCHARTWINDOW_H

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "cyclesData.h"
#include "configClass.h"
#include "chart.h"
#include "utilClass.h"

/**
 * windows to display statistic chart
 */
class customChartWindow: public wxScrolledWindow
{
    // VARIABLES
private:
    DECLARE_EVENT_TABLE()

    wxWindow *m_parent;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    //drawingClass *m_drawing;
    wxScrolledWindow *m_notesWindow;

    utilClass m_util;
    //int m_pixelsPerUnitX;
    //int m_noUnitsX;

public:
    enum {
        ID_NOTESWINDOW = 3101,
        ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
    };
    // METHODS
public:
    customChartWindow(wxWindow *parent, configClass *config, cycleDataClass *cycleData, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxScrolledWindowStyle, const wxString& name = wxPanelNameStr);
    virtual ~customChartWindow();

    void setChart(chart*, bool refreshData = false);

    void OnPaint(wxPaintEvent &event);
    void OnMouseClick(wxMouseEvent &event);
    void OnMouseDClick(wxMouseEvent &event);
    void OnMouseMotion(wxMouseEvent &event);

protected:
private:
    chart *m_chart;
    int a;
};

#endif // CUSTOMCHARTWINDOW_H
