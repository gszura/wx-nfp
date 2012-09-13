/*******************************************************************************
//
// Name:        lutealPhasesChart.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "lutealPhasesChart.h"

/******************************************************************************/

/*******************************************************************************
********************************************************************************
*******************************************************************************/

lutealPhasesChart::lutealPhasesChart(configClass *config, cycleDataClass *cycleData)
    : chart(config, cycleData, _("luteal phase in cycles"), _("Luteal phases length in all cycles (normal type)"))
{
    //ctor
}

lutealPhasesChart::~lutealPhasesChart()
{
    //dtor
}

/**
 * Force updating chart data
 */
void lutealPhasesChart::updateChartData()
{
    // TODO
    //initData();
}

/**
 * Print chart without updating data
 */
void lutealPhasesChart::printChart(int width, int height, wxDC &dc)
{
    wxColour barColour = wxColour(100, 255, 100);

    int cardsCount = m_cycleData->getCardsCount();
    int longestPhase = 0;

    wxArrayInt data;
    data.Alloc(cardsCount);

    for (int c=1; c<=m_cycleData->getCardsCount(); c++) {
        cardEntry *card = m_cycleData->getCard(c);

        if ( card->getCycleType() == CYCLE_TYPE_NORMAL && card->isResultTemperatureLevelSet() )
            data.Add(card->getDaysCount() - card->getResultTemperatureHighLevelStart() + 1);
        else
            data.Add(0);

        if (longestPhase < data[c-1])
            longestPhase = data[c-1];
    }

    wxArrayString namesLeft;
    namesLeft.Add(m_util.intToStr(longestPhase));
    namesLeft.Add(_("no of\ndays"));

    wxArrayString namesTop;
    namesTop.Add(_("no of\ndays"));

    wxArrayString namesBottom;
    namesBottom.Add(m_util.intToStr(cardsCount));
    namesBottom.Add(_("cycle"));

    wxArrayString legendNames;
    legendNames.Add(_("luteal\nphase\nlength"));

    wxArrayColour legendColours;
    legendColours.Add(barColour);

    calculateMargins(dc, width, height, &namesLeft, &legendNames, &namesTop, &namesBottom, longestPhase, cardsCount);
    drawAxisVertical(dc, _("no of\ndays"), longestPhase, 2);
    drawAxisHorizontal(dc, _("cycle"), cardsCount);
    drawLegend(dc, &legendNames, &legendColours );

    drawBarPlot(dc, &data, barColour);
}

