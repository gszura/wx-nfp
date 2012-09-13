/*******************************************************************************
//
// Name:        chart.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "chart.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(wxArrayColour);

/*******************************************************************************
********************************************************************************
*******************************************************************************/

chart::chart(configClass *config, cycleDataClass *cycleData, wxString name, wxString title)
{
    m_name = name;
    m_title = title;
    m_config = config;
    m_cycleData = cycleData;

    m_marginLeft = 0;
    m_marginTop = 0;
    m_marginBottom = 0;
    m_marginRight = 0;
    m_x0 = 0;
    m_y0 = 0;
    m_chartWidth = 0;
    m_chartHeight = 0;
    m_onePointWidth = 0;
    m_onePointHeight = 0;
    m_legendX = 0;
}

chart::~chart()
{
    //dtor
}

wxString chart::getName()
{
    return m_name;
};

wxString chart::getTitle()
{
    return m_title;
};

/******************************************************************************/

/**
 * Update data and print chart
 */
void chart::updateChartData()
{
    // nothing
}

/**
 * Print chart without updating data
 */
/**
 *
 */
void chart::printChart(int width, int height, wxDC &dc)
{
    // nothing
}

/******************************************************************************/

/**
 *
 */
void chart::drawTitle(wxDC &dc)
{
    dc.SetFont( m_config->fontHeadTopic );
    dc.SetTextForeground( m_config->fontHeadTopicColour );
    dc.DrawText( m_title, m_marginLeft + 10, 1);
}

/**
 *
 */
void chart::drawLegend(wxDC &dc, wxArrayString *entries, wxArrayColour *colours)
{
    int legendY = m_marginTop + 5;

    for (int i=0; i<entries->GetCount(); i++) {
        dc.SetPen( wxPen( colours->Item(i) ) );
        dc.SetBrush( wxBrush( colours->Item(i) ) );
        dc.DrawRectangle( m_legendX, legendY, m_marginRight - 4, 10 );
        legendY += 11;
        int w, h;
        dc.DrawText(entries->Item(i), m_legendX, legendY);
        dc.GetTextExtent( entries->Item(i), &w, &h );
        legendY += h + 5;
    }
}

/******************************************************************************/

/**
 * if density == -1 => autocalculate
 */
void chart::drawAxisVertical(wxDC &dc, wxString axisName, int numberOfPoints, int density, bool drawChartLines, bool inTheMiddle)
{
    int w, h;

    if (density == -1) {
        // calculating density
        dc.GetTextExtent( wxString::Format(_T("%i"), numberOfPoints), &w, &h );

        density = h / m_onePointHeight + 1;
        if (m_onePointHeight * density - h < 2) density++;
    }

    int yRows = (numberOfPoints / density) + 1;
    dc.GetTextExtent( m_util.intToStr(numberOfPoints), &w, &h );


    // main vertical line
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.DrawLine( m_x0, m_y0, m_x0, m_y0 - m_chartHeight );

    // graph's Y labels
    int yLine = m_y0 - density * m_onePointHeight;
    int yPoint = m_y0 - density * m_onePointHeight + (inTheMiddle ? m_onePointHeight / 2 : 0);

    for (int i=1; i<=yRows; i++) {
        if (i*density > numberOfPoints)
            break;

        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLabel( wxString::Format(_T("%i"), i*density), wxRect( m_x0-5-w, yPoint-h/2, w, h ), wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT );
        dc.DrawLine( m_x0, yPoint, m_x0 - 5, yPoint );
        if (drawChartLines) {
            dc.SetPen( wxPen( wxColour(220, 220, 220) ) );
            dc.DrawLine( m_x0, yLine, m_x0 + m_chartWidth, yLine );
        }
        yPoint -= density * m_onePointHeight;
        yLine -= density * m_onePointHeight;
    }

    dc.DrawText(axisName, 1, 1);
}

/**
 * if density == -1 => autocalculate
 */
void chart::drawAxisVertical(wxDC &dc, wxString axisName, wxArrayString *points, int density, bool drawChartLines, bool inTheMiddle)
{
    int w, h;

    if (density == -1) {
        // calculating density
        dc.GetTextExtent(points->Item(0), &w, &h );

        density = h / m_onePointHeight + 1;
        if (m_onePointHeight * density - h < 2) density++;
    }

    int yRows = (points->GetCount() / density) + 1;
    dc.GetTextExtent( points->Item(0), &w, &h );


    // main vertical line
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.DrawLine( m_x0, m_y0, m_x0, m_y0 - m_chartHeight );

    // graph's Y labels
    int yLine = m_y0 - density * m_onePointHeight;
    int yPoint = m_y0 - density * m_onePointHeight + (inTheMiddle ? m_onePointHeight / 2 : 0);

    for (int i=1; i<=yRows; i++) {
        if (i*density > points->GetCount())
            break;

        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLabel( points->Item(i*density-1), wxRect( m_x0-5-w, yPoint-h/2, w, h ), wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT );
        dc.DrawLine( m_x0, yPoint, m_x0 - 5, yPoint );
        if (drawChartLines) {
            dc.SetPen( wxPen( wxColour(220, 220, 220) ) );
            dc.DrawLine( m_x0, yLine, m_x0 + m_chartWidth, yLine );
        }
        yPoint -= density * m_onePointHeight;
        yLine -= density * m_onePointHeight;
    }

    dc.DrawText(axisName, 1, 1);
}

/******************************************************************************/

/**
 *
 */
void chart::drawAxisHorizontal(wxDC &dc, wxString axisName, int numberOfPoints, int density, bool drawChartLines, bool inTheMiddle)
{
    int w, h;

    if (density == -1) {
        // calculating density
        dc.GetTextExtent( wxString::Format(_T("%i"), numberOfPoints), &w, &h );

        density = w / m_onePointWidth + 1;
        if (m_onePointWidth * density - w < 3) density++;
    }

    int xRows = (numberOfPoints / density) + 1;
    dc.GetTextExtent( wxString::Format(_T("%i"), numberOfPoints), &w, &h );

    // main horizonatal line
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.DrawLine( m_x0, m_y0, m_x0 + m_chartWidth, m_y0 );

    // graph's X labels
    int xLine = m_x0 + density * m_onePointWidth;
    int xPoint = m_x0 + density * m_onePointWidth - (inTheMiddle ? m_onePointWidth / 2 : 0);

    for (int i=1; i<=xRows; i++) {
        if (i*density > numberOfPoints)
            break;

        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLabel(  wxString::Format(_T("%i"), i*density), wxRect( xPoint - w/2, m_y0 + 5, w, h ), wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER );
        dc.DrawLine( xPoint, m_y0, xPoint, m_y0 + 5 );
        if (drawChartLines) {
            dc.SetPen( wxPen( wxColour(220, 220, 220) ) );
            dc.DrawLine( xLine, m_y0, xLine, m_y0 - m_chartHeight );
        }
        xPoint += density * m_onePointWidth;
        xLine += density * m_onePointWidth;
    }

    dc.DrawText(axisName, m_x0 + m_chartWidth, m_y0+5);
}

/**
 *
 */
void chart::drawAxisHorizontal(wxDC &dc, wxString axisName, wxArrayString *points, int density, bool drawChartLines, bool verticalNames, bool inTheMiddle)
{
    int w, h;

    if (density == -1) {
        // TODO
        density = 1;
    }

    int xRows = (points->GetCount() / density) + 1;

    // main horizonatal line
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.DrawLine( m_x0, m_y0, m_x0 + m_chartWidth, m_y0 );

    int xLine = m_x0 + density * m_onePointWidth;
    int xPoint = m_x0 + density * m_onePointWidth - (inTheMiddle ? m_onePointWidth / 2 : 0);

    for (int i=1; i<=xRows; i++) {
        if (i*density > points->GetCount())
            break;

        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.GetTextExtent( points->Item(i*density-1), &w, &h );
        if (!verticalNames) {
            dc.DrawLabel( points->Item(i*density-1), wxRect( xPoint - w/2, m_y0 + 5, w, h ), wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER );
        } else {
            dc.DrawRotatedText( points->Item(i*density-1), xPoint - h/2, m_y0 + 5 + w, 90 );
        }
        dc.DrawLine( xPoint, m_y0, xPoint, m_y0 + 5 );
        if (drawChartLines) {
            dc.SetPen( wxPen( wxColour(220, 220, 220) ) );
            dc.DrawLine( xLine , m_y0, xLine, m_y0 - m_chartHeight );
        }
        xPoint += density * m_onePointWidth;
        xLine += density * m_onePointWidth;
    }
    dc.DrawText( axisName, m_x0 + m_chartWidth, m_y0+5 );
}

/******************************************************************************/

/**
 *
 */
void chart::drawBarPlot(wxDC &dc, wxArrayInt *data, wxColour colour)
{
    int x = m_x0 + 3;
    for (int i=0; i<data->GetCount(); i++) {
        dc.SetPen( wxPen( colour ) );
        dc.SetBrush( wxBrush( colour ) );
        dc.DrawRectangle(x, m_y0 - m_onePointHeight * data->Item(i), m_onePointWidth-3, m_onePointHeight * data->Item(i));
        x += m_onePointWidth;
    }
}

/******************************************************************************/

/**
 *
 */
void chart::calculateMargins(wxDC &dc, int width, int height, wxArrayString *namesLeft, wxArrayString *namesRight, wxArrayString *namesTop, wxArrayString *namesBottom, int verticalPointsCount, int horizontalPointsCount, bool verticalNames)
{
    m_marginLeft = 0;
    m_marginTop = 0;
    m_marginBottom = 0;
    m_marginRight = 0;
    m_x0 = 0;
    m_y0 = 0;
    m_chartWidth = 0;
    m_chartHeight = 0;
    m_onePointWidth = 0;
    m_onePointHeight = 0;
    m_legendX = 0;

    int w, h;
    dc.SetFont( m_config->fontHeadTopic );
    dc.SetTextForeground( m_config->fontHeadTopicColour );
    for (int i=0; i<namesTop->GetCount(); i++) {
        dc.GetTextExtent( namesTop->Item(i), &w, &h );
        if (m_marginTop < h)
            m_marginTop = h;
    }
    m_marginTop+=5;

    dc.SetFont( m_config->fontResultDefault );
    dc.SetTextForeground( m_config->fontResultDefaultColour );
    w = h = 0;
    for (int i=0; i<namesLeft->GetCount(); i++) {
        dc.GetTextExtent( namesLeft->Item(i), &w, &h );
        if (m_marginLeft < w)
            m_marginLeft = w;
    }
    m_marginLeft+=2;

    w = h = 0;
    for (int i=0; i<namesRight->GetCount(); i++) {
        dc.GetTextExtent( namesRight->Item(i), &w, &h );
        if (m_marginRight < w)
            m_marginRight = w;
    }
    m_marginRight+=5;

    w = h = 0;
    for (int i=0; i<namesBottom->GetCount(); i++) {
        dc.GetTextExtent( namesBottom->Item(i), &w, &h );
        if (verticalNames) {
            if (m_marginBottom < w)
                m_marginBottom = w;
        } else {
            if (m_marginBottom < h)
                m_marginBottom = h;
        }
    }
    m_marginBottom+=8;

    m_x0 = m_marginLeft;
    m_y0 = height - m_marginBottom;
    m_legendX = width - m_marginRight + 2;

    m_chartWidth = width - m_marginLeft - m_marginRight;
    m_chartHeight = height - m_marginTop - m_marginBottom;

    m_onePointWidth = m_chartWidth / horizontalPointsCount;
    if (m_onePointWidth * horizontalPointsCount > m_chartWidth + 5)
        m_onePointWidth--;

    m_onePointHeight = m_chartHeight / verticalPointsCount;
    if (m_onePointHeight * verticalPointsCount > m_chartHeight + 5)
        m_onePointHeight--;


    /*
    wxString debugMsg = wxEmptyString;
    debugMsg << _T("width = ") << width;
    debugMsg << _T("height = ") << height << _T("\n");
    debugMsg << _T("m_marginLeft = ") << m_marginLeft << _T("\n");
    debugMsg << _T("m_marginTop = ") << m_marginTop << _T("\n");
    debugMsg << _T("m_marginBottom = ") << m_marginBottom << _T("\n");
    debugMsg << _T("m_marginRight = ") << m_marginRight << _T("\n");
    debugMsg << _T("m_x0 = ") << m_x0 << _T("\n");
    debugMsg << _T("m_y0 = ") << m_y0 << _T("\n");
    debugMsg << _T("m_chartWidth = ") << m_chartWidth << _T("\n");
    debugMsg << _T("m_chartHeight = ") << m_chartHeight << _T("\n");
    debugMsg << _T("m_onePointWidth = ") << m_onePointWidth << _T("\n");
    debugMsg << _T("m_onePointHeight = ") << m_onePointHeight << _T("\n");
    debugMsg << _T("m_legendX = ") << m_legendX << _T("\n");
    dc.DrawText(debugMsg, 100, 100);
    */

}

/******************************************************************************/
