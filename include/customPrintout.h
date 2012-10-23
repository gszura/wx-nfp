/*******************************************************************************
//
// Name:        customPrintout.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __CUSTOM_PRINTOUT__
#define __CUSTOM_PRINTOUT__

#include "wx/print.h"
#include "wx/printdlg.h"

#include "configClass.h"
#include "cyclesData.h"
#include "drawingClass.h"
#include "utilClass.h"

// cell height (in milimeters * 10) - current value: 3.2 mm
#define CELLHEIGHT  32

/******************************************************************************/

class customPrintout: public wxPrintout
{
    // VARIABLES
public:

private:

    configClass *m_config;
    cycleDataClass *m_cycleData;
    drawingClass *m_drawing;
    utilClass m_util;

    // first printed card
    int m_firstCard;

    // last printed card
    int m_lastCard;

    // should legend be printed or not
    bool m_printLegend;

    // true if the legend has been printed
    bool m_legendPrinted;

    // m_maxHeight of the printed card (including place for days' notes) - needed to calculate a scaling factor
    int m_maxHeight;

    // m_maxWidth of the card, if card width is > m_maxWidth than it has to printed on more than one page
    // value of m_maxWidth is calculated based on print page size and m_scale factor.
    int m_maxWidth;

    // Calculated a scaling factor
    float m_scale;

    // currently printed card
    int m_currentCard;

    // currently printed page (counted from one for each card)
    int m_currentPage;

    // value indicating on how many pages the current card will be printed (calculated for each card)
    int m_numberOfPages;

    // first day of each page (calculated for each card)
    int m_startDays[30];

    // Y-coordinate where additional notes starts
    int m_notesStartY;

    // METHODS
public:
    customPrintout (configClass *config,
                    cycleDataClass *cycleData,
                    int firstCard, int lastCard, bool printLegend,
                    wxString title = _("wx-nfp") );
    virtual ~customPrintout();

    bool OnBeginDocument (int startPage, int endPage);
    //void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);
    bool HasPage (int page);
    bool OnPrintPage (int page);

private:
    void CalculateUserScale (wxDC *dc);
    void CalculatePagesNumber (wxDC *dc);

    void PrintPage (wxDC *dc);
    void PrintAdditionalNotes (wxDC *dc);
    void PrintLegend (wxDC *dc);
    void PrintLegendHeader (wxDC *dc, wxString header, int x, int y);
    void PrintLegendEntry (wxDC *dc, wxString str1, wxString str3, int x1, int x2, int x3, int y);
    void PrintLegendCervixEntry (wxDC *dc, int p, int d, wxString str3, int x1, int x2, int x3, int y, int h, int w);
};



/******************************************************************************/
#endif // __CUSTOM_PRINTOUT__

