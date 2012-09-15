/*******************************************************************************
//
// Name:        temperaturesChart.cpp
// Author:      inspired by szybig 'cycleGraph'
// Description:
//
*******************************************************************************/

#include "temperaturesChart.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(wxArrayTemperatures);

temperaturesChart::temperaturesChart(configClass *config, cycleDataClass *cycleData)
    : chart(config, cycleData, _("temperature in cycles"), _("How many times the same temperature has been mesured in the same cycle day"))
{
    m_daysCount = 0;
}

temperaturesChart::~temperaturesChart()
{
    //dtor
}

/**
 * Update data and print chart
 */
void temperaturesChart::updateChartData()
{
    initData();
}

/**
 * Print chart without updating data
 */
void temperaturesChart::printChart(int width, int height, wxDC &dc)
{
    if (m_daysCount == 0)
        initData();

    wxArrayString namesLeft;
    namesLeft.Add(_T("37,45"));
    namesLeft.Add(_("temperature"));

    wxArrayString namesTop;
    namesTop.Add(_("temperature"));

    wxArrayString namesBottom;
    namesBottom.Add(m_util.intToStr(m_daysCount));
    namesBottom.Add(_("day of cycle"));

    wxArrayString namesRight;
    namesRight.Add(wxString::Format( _( "%d times" ), m_maxCount ) + _T("abla"));



    calculateMargins(dc, width, height, &namesLeft, &namesRight, &namesTop, &namesBottom, m_tempPointsCount, m_daysCount);
    drawAxisVertical(dc, _("temperature"), &m_points, -1, true, true);
    drawAxisHorizontal(dc, _("day of cycle"), m_daysCount, -1, true);

    drawTemperaturesLegend(dc);
    drawTemperaturesMatrix(dc);
}




void temperaturesChart::initData()
{
    m_daysCount = getNumberOfDaysInLongestNormalCycle();
    m_data.Clear();
    m_points.Clear();


    // init data array
    for (int i=0; i<=m_daysCount; i++) {
        temperaturesMap m;
        m_data.Add(m);
    }

    m_minTemp = 9999;
    m_maxTemp = 0;
    m_maxCount = 0;

    for( int i = 1; i <= m_cycleData->getCardsCount(); i++ ) {
        cardEntry *card = m_cycleData->getCard(i);

        if ( card->getCycleType() == CYCLE_TYPE_AFTER_PREGNANCY || card->getCycleType() == CYCLE_TYPE_PERI_MENOPAUSE )
            continue;

        int daysCount = card->getDaysCount();
        if ( card->getCycleType() == CYCLE_TYPE_PREGNANCY && daysCount > m_daysCount )
            daysCount = m_daysCount;

        for( int day=1; day<=daysCount; day++ ) {
            if (card->getDay(day)->getTemperatureDisturbances())
                continue;

            int temperature = card->getDay(day)->getTemperatureValueAfterCorrections();
            if (temperature <= 0)
                continue;

            m_data[day][temperature]++;

            if (m_maxCount < m_data[day][temperature])
                m_maxCount = m_data[day][temperature];

            if( temperature > m_maxTemp )
                m_maxTemp = temperature;

            if(temperature < m_minTemp)
                m_minTemp = temperature;
        }
    }

    if (m_minTemp == 9999)
        m_minTemp = 3660;

    if (m_maxTemp == 0)
        m_maxTemp = 3750;

    m_tempPointsCount = (m_maxTemp - m_minTemp) / STEP + 1;

    m_points.Clear();
    for (int t=m_minTemp; t<=m_maxTemp; t+=STEP) {
        m_points.Add( m_util.temperatureToStr(t) );
    }

}

int temperaturesChart::getNumberOfDaysInLongestNormalCycle()
{
    int maxDays = 0;

    for( int i = 1; i <= m_cycleData->getCardsCount(); i++ ) {
        cardEntry *card = m_cycleData->getCard(i);
        if ( card->getCycleType() == CYCLE_TYPE_NORMAL) {
            int days = card->getDaysCount();
            if( days > maxDays ) maxDays = days;
        }
    }
    if( maxDays == 0 ) maxDays = 28;
    return maxDays;
}

/**
 *
 */
void temperaturesChart::drawTemperaturesLegend(wxDC &dc)
{
    int textWidth, textHeight, legendY = m_marginTop + 5;
    wxString str = wxString::Format( _( "%d times" ), m_maxCount );
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.GetMultiLineTextExtent( str, &textWidth, &textHeight );

    int cellHeight = ( m_chartHeight + m_marginTop - legendY ) / ( m_maxCount + 1 );
    if (cellHeight > m_onePointHeight) cellHeight = m_onePointHeight;
    int cellWidth = m_marginRight / 2;
    if (cellWidth > m_onePointWidth) cellWidth = m_onePointWidth;

    if ( cellWidth + m_marginRight / 2 > textWidth ) {
        textWidth = cellWidth + m_marginRight / 2;
    } else {
        cellWidth = textWidth - m_onePointWidth;
    }

    dc.DrawLabel( str, wxRect( m_legendX, legendY, textWidth, textHeight ), wxALIGN_RIGHT );
    legendY += textHeight + 1;

    dc.SetPen( wxPen( wxColour(220, 220, 220) ));

    for ( int i = m_maxCount; i >= 1; i-- ) {
        int c = 375 * i / m_maxCount;
        unsigned char red = (unsigned char)(255 - c);
        unsigned char green = (unsigned char)255;
        unsigned char blue = (unsigned char)(255 - c);
        if (c > 255) {
            red = (unsigned char)0;
            green = (unsigned char)(255 * 2 - c);
            blue = (unsigned char)0;
        }

        dc.SetBrush( wxBrush( wxColour(red, green, blue) ));
        dc.DrawRectangle( m_legendX + m_marginRight / 2, legendY, cellWidth, cellHeight);
        legendY += cellHeight;
    }

    dc.SetBrush( wxBrush( wxColour(255, 255, 255) ));
    dc.DrawRectangle( m_legendX + m_marginRight / 2, legendY, cellWidth, cellHeight);
    legendY += cellHeight + 1;

    str = wxString::Format( _( "%d times" ), 0 );
    dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
    dc.DrawLabel( str, wxRect( m_legendX, legendY, textWidth, textHeight ), wxALIGN_RIGHT );
}

/**
 *
 */
void temperaturesChart::drawTemperaturesMatrix(wxDC &dc)
{
    for (int d=0; d<=m_daysCount; d++) {
        int y = 1;
        for (int t=m_minTemp; t<=m_maxTemp; t+=STEP) {
            if ( m_data[d].count(t) > 0 ) {
                int c = 375 * m_data[d][t] / m_maxCount;
                unsigned char red = (unsigned char)(255 - c);
                unsigned char green = (unsigned char)255;
                unsigned char blue = (unsigned char)(255 - c);
                if (c > 255) {
                    red = (unsigned char)0;
                    green = (unsigned char)  (255 * 2 - c);
                    blue = (unsigned char)0;
                }
                dc.SetPen( wxPen( wxColour(red, green, blue) ));
                dc.SetBrush( wxBrush( wxColour(red, green, blue) ));
                dc.DrawRectangle( m_x0 + (d-1) * m_onePointWidth + 1, m_y0 - m_onePointHeight * y - 1, m_onePointWidth, m_onePointHeight );
            }
            y++;
        }
    }
}
