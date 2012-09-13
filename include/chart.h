/*******************************************************************************
//
// Name:        chart.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef CHART_H
#define CHART_H

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"

#include <wx/arrstr.h>
#include <wx/dynarray.h>

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/******************************************************************************/

WX_DECLARE_OBJARRAY(wxColour, wxArrayColour);


/*******************************************************************************
********************************************************************************
*******************************************************************************/

class chart
{
public:
    chart(configClass *config, cycleDataClass *cycleData, wxString name = wxEmptyString, wxString title = _("Select statistic to display"));
    virtual ~chart();

    wxString getName();
    wxString getTitle();

    void drawTitle(wxDC&);

    virtual void updateChartData();
    virtual void printChart(int, int, wxDC&);
protected:
    void drawLegend(wxDC&, wxArrayString*, wxArrayColour*);
    void drawAxisVertical(wxDC &dc, wxString axisName, int numberOfPoints, int density = -1, bool drawChartLines = true, bool inTheMiddle = false);
    void drawAxisVertical(wxDC &dc, wxString axisName, wxArrayString *points, int density = -1, bool drawChartLines = true, bool inTheMiddle = false);
    void drawAxisHorizontal(wxDC &dc, wxString axisName, int numberOfPoints, int density = -1, bool drawChartLines = false, bool inTheMiddle = true);
    void drawAxisHorizontal(wxDC &dc, wxString axisName, wxArrayString *points, int density = -1, bool drawChartLines = false, bool verticalNames = false, bool inTheMiddle = true);

    void drawBarPlot(wxDC&, wxArrayInt*, wxColour);

    void calculateMargins(wxDC &dc, int width, int height, wxArrayString *namesLeft, wxArrayString *namesRight, wxArrayString *namesTop, wxArrayString *namesBottom, int verticalPointsCount, int horizontalPointsCount, bool verticalNames = false);

    configClass *m_config;
    cycleDataClass* m_cycleData;
    wxString m_name;
    wxString m_title;
    utilClass m_util;

    int m_marginLeft;
    int m_marginTop;
    int m_marginBottom;
    int m_marginRight;
    int m_x0;
    int m_y0;
    int m_chartWidth;
    int m_chartHeight;
    int m_onePointWidth;
    int m_onePointHeight;
    int m_legendX;
private:
};

#endif // CHART_H

/******************************************************************************/
