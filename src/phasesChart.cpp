/*******************************************************************************
//
// Name:        phasesChart.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "phasesChart.h"

/******************************************************************************/

/*******************************************************************************
********************************************************************************
*******************************************************************************/

phasesChart::phasesChart(configClass *config, cycleDataClass *cycleData)
    : chart(config, cycleData, _("phases in cycles"), _("Phases length in all cycles"))
{
    //ctor
}

phasesChart::~phasesChart()
{
    //dtor
}

/**
 * Force updating chart data
 */
void phasesChart::updateChartData()
{
    // TODO
    //initData();
}

/**
 * Print chart without updating data
 */
void phasesChart::printChart(int width, int height, wxDC &dc)
{
    wxColour phase1Colour = wxColour(100, 100, 255);
    wxColour phase2Colour = wxColour(255, 100, 100);
    wxColour phase3Colour = wxColour(100, 255, 100);
    wxColour phaseNotCalculatedColour = wxColour(255, 255, 100);
    wxColour postPregnancyColour = wxColour(255, 200, 255);

    int cardsCount = m_cycleData->getCardsCount();
    int longestCycle = 0;

    wxArrayInt fertilePhaseStartValues;
    wxArrayInt infertilePhaseStartValues;
    wxArrayInt cycleLengthValues;
    wxArrayInt cycleTypes;

    fertilePhaseStartValues.Alloc(cardsCount);
    infertilePhaseStartValues.Alloc(cardsCount);
    cycleLengthValues.Alloc(cardsCount);
    cycleTypes.Alloc(cardsCount);

    for (int c=1; c<=m_cycleData->getCardsCount(); c++) {
        cardEntry *card = m_cycleData->getCard(c);

        cycleTypes.Add(card->getCycleType());

        if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
            if (card->isResultFertilePhaseStartSet())
                fertilePhaseStartValues.Add(card->getResultFertilePhaseStart()[0]);
            else
                fertilePhaseStartValues.Add(0);

            if (card->isResultInfertilePhaseStartSet())
                infertilePhaseStartValues.Add(card->getResultInfertilePhaseStart()[0]);
            else
                infertilePhaseStartValues.Add(0);

            cycleLengthValues.Add(card->getDaysCount());

            if (card->getCycleType() == CYCLE_TYPE_NORMAL && longestCycle < card->getDaysCount()) {
                longestCycle = card->getDaysCount();
            }
        } else {
            fertilePhaseStartValues.Add(0);
            infertilePhaseStartValues.Add(0);
            cycleLengthValues.Add(card->getDaysCount());
        }
    }

    wxArrayString namesLeft;
    namesLeft.Add(m_util.intToStr(longestCycle));
    namesLeft.Add(_("no of\ndays"));

    wxArrayString namesTop;
    namesTop.Add(_("no of\ndays"));

    wxArrayString namesBottom;
    namesBottom.Add(m_util.intToStr(cardsCount));
    namesBottom.Add(_("cycle"));

    wxArrayString legendNames;
    legendNames.Add(_("I phase"));
    legendNames.Add(_("II phase"));
    legendNames.Add(_("III phase"));
    legendNames.Add(_("phases not\ncalculated"));
    legendNames.Add(_("after-pregnancy\nor peri-menopause"));

    wxArrayColour legendColours;
    legendColours.Add(phase1Colour);
    legendColours.Add(phase2Colour);
    legendColours.Add(phase3Colour);
    legendColours.Add(phaseNotCalculatedColour);
    legendColours.Add(postPregnancyColour);

    calculateMargins(dc, width, height, &namesLeft, &legendNames, &namesTop, &namesBottom, longestCycle, cardsCount);
    drawAxisVertical(dc, _("no of\ndays"), longestCycle, 5);
    drawAxisHorizontal(dc, _("cycle"), cardsCount);
    drawLegend(dc, &legendNames, &legendColours );


    int x = m_x0 + 2;
    for (int i=0; i<cardsCount; i++) {
        if (cycleTypes[i] == CYCLE_TYPE_AFTER_PREGNANCY || cycleTypes[i] == CYCLE_TYPE_PERI_MENOPAUSE) {
            dc.SetPen( wxPen( postPregnancyColour ) );
            dc.SetBrush( wxBrush( postPregnancyColour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * cycleLengthValues[i], m_onePointWidth-3, m_onePointHeight * cycleLengthValues[i]);
        } else if (infertilePhaseStartValues[i] > 0 && fertilePhaseStartValues[i] > 0) {
            dc.SetPen( wxPen( phase3Colour ) );
            dc.SetBrush( wxBrush( phase3Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * cycleLengthValues[i], m_onePointWidth-3, m_onePointHeight * cycleLengthValues[i]);
            dc.SetPen( wxPen( phase2Colour ) );
            dc.SetBrush( wxBrush( phase2Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * infertilePhaseStartValues[i], m_onePointWidth-3, m_onePointHeight * infertilePhaseStartValues[i]);
            dc.SetPen( wxPen( phase1Colour ) );
            dc.SetBrush( wxBrush( phase1Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * fertilePhaseStartValues[i], m_onePointWidth-3, m_onePointHeight * fertilePhaseStartValues[i]);
        } else if (infertilePhaseStartValues[i] > 0) {
            dc.SetPen( wxPen( phase3Colour ) );
            dc.SetBrush( wxBrush( phase3Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * cycleLengthValues[i], m_onePointWidth-3, m_onePointHeight * cycleLengthValues[i]);
            dc.SetPen( wxPen( phase2Colour ) );
            dc.SetBrush( wxBrush( phase2Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * infertilePhaseStartValues[i], m_onePointWidth-3, m_onePointHeight * infertilePhaseStartValues[i]);
        } else if (fertilePhaseStartValues[i] > 0) {
            dc.SetPen( wxPen( phase2Colour ) );
            dc.SetBrush( wxBrush( phase2Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * cycleLengthValues[i], m_onePointWidth-3, m_onePointHeight * cycleLengthValues[i]);
            dc.SetPen( wxPen( phase1Colour ) );
            dc.SetBrush( wxBrush( phase1Colour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * fertilePhaseStartValues[i], m_onePointWidth-3, m_onePointHeight * fertilePhaseStartValues[i]);
        } else {
            dc.SetPen( wxPen( phaseNotCalculatedColour ) );
            dc.SetBrush( wxBrush( phaseNotCalculatedColour ) );
            dc.DrawRectangle(x, m_y0 - m_onePointHeight * cycleLengthValues[i], m_onePointWidth-3, m_onePointHeight * cycleLengthValues[i]);
        }
        x += m_onePointWidth;
    }
}
