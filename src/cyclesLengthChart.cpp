/*******************************************************************************
//
// Name:        cyclesLengthChart.cpp
// Author:      Grzegorz Szura
//              based on szybig 'histogramsFrame'
// Description:
//
*******************************************************************************/

#include "cyclesLengthChart.h"
#include <vector>
using namespace std;

/******************************************************************************/

/*******************************************************************************
********************************************************************************
*******************************************************************************/

cyclesLengthChart::cyclesLengthChart(configClass *config, cycleDataClass *cycleData)
    : chart(config, cycleData, _("cycles length"), _("Number of cycles with particular length"))
{
    //ctor
}

cyclesLengthChart::~cyclesLengthChart()
{
    //dtor
}

/**
 * Force updating chart data
 */
void cyclesLengthChart::updateChartData()
{
    // TODO
    //initData();
}

/**
 * Print chart without updating data
 */
void cyclesLengthChart::printChart(int width, int height, wxDC &dc)
{
    wxColour barColour = wxColour(100, 255, 100);

    vector<int> items;
    wxArrayInt data;
    wxArrayString points;
    int maxValue = 0;
    int elementsCount = 0;

    for(int i=1; i<=m_cycleData->getCardsCount(); i++) {
        int days = m_cycleData->getCard(i)->getDaysCount();
        while( (int)items.size() < days+1 )
            items.push_back( 0 );
        items[days]++;
    }

    struct chartItem {
        wxString name;
        int value;
    };

    for (size_t i = 0; i < items.size(); i++) {
        if ( items[i] > maxValue )
            maxValue = items[i];

        if (items[i] > 0)
            elementsCount++;
    }

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i] > 0) {
            points.Add(m_util.intToStr(i));
            data.Add(items[i]);
        }
    }

    wxArrayString namesLeft;
    namesLeft.Add(m_util.intToStr(maxValue));
    namesLeft.Add(_("no of\ncycles"));

    wxArrayString namesTop;
    namesTop.Add(_("no of\ncycles"));

    wxArrayString namesBottom;
    namesBottom.Add(m_util.intToStr(elementsCount));
    namesBottom.Add(_("cycle\nlength"));

    wxArrayString legendNames;
    legendNames.Add(_("no of\ncycles\nwith this\nlenght"));

    wxArrayColour legendColours;
    legendColours.Add(barColour);

    calculateMargins(dc, width, height, &namesLeft, &legendNames, &namesTop, &namesBottom, maxValue, elementsCount);
    drawAxisVertical(dc, _("no of\ncycles"), maxValue, 1);
    drawAxisHorizontal(dc, _("cycle\nlength"), &points);
    drawLegend(dc, &legendNames, &legendColours );

    drawBarPlot(dc, &data, barColour);
}
