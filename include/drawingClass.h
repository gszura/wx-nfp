/*******************************************************************************
//
// Name:        drawingClass.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __DRAWING_CLASS__
#define __DRAWING_CLASS__

#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class drawingClass
{
public:
    /** Contructor */
    //drawingClass(configClass *config, cycleDataClass *cycleData);
    drawingClass (configClass *config, cycleDataClass *cycleData, bool printing = false);

    /** WINDOW TOP */
    void drawInfoHead (wxDC &dc, int cardNo, int pageNo = -1);

    /** WINDOW LEFT */
    void drawHeader (wxDC &dc, int cardNo);
    void drawCardDataInHeader (wxDC &dc, int cardNo);

    /** WINDOW MAIN */
    void drawCard (wxDC &dc, int cardNo, int firstDay, int lastDay);
    void drawDay (wxDC &dc, int cardNo, int dayNo, int x0, wxDateTime date, wxString usualMeasurementTime);
    void drawTemperatureGraph (wxDC &dc, int cardNo, int firstDay = 1);
    bool isPhaseChangeInNext3Days(cardEntry *card, int fromDay);
    void markDay( wxDC &dc, int cardNo, int dayNo, bool doMark );
    void markRow( wxDC &dc, int rowNo, bool doMark );

private:
    void drawCellBackground (wxDC &dc, int dayNo, int row, int x, int y, int w, int h);
    void drawText (wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int align, wxString text);
    void drawCrossOrSlash (wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int data);
    void drawSexualRelation (wxDC &dc, int dayNo, int row, int x, int y, int w, int h, dayEntry * day);
    void drawHeart( wxDC &dc, int x1, int y1 );
    void drawVV (wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int data);
public:
    void drawCervixOval (wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int position, int dilation);

public:
    /** SET PARAMETERS (WIDTH, HEIGHT) */
    int setWindowTopHeight (wxDC &dc);
    void setWindowTopEntriesStartX (wxDC &dc);
    int setHeaderWidth (wxDC &dc);
    int setCellHeight (wxDC &dc);
    void setCellsWidth (wxDC &dc, int cardNo);
    void setCellWidth (wxDC &dc, int cardNo, int dayNo);
    int getCellWidth (int day);
    int getCellHeight();

public:
    /** SET COLOURS AND FONTS */
    void setCellColour (wxDC &dc, int day, int row);
    void setFontHeadTopic (wxDC &dc);
    void setFontHeadName (wxDC &dc);
    void setFontHeadValue (wxDC &dc);
    void setFontResultHeader (wxDC &dc);
    void setFontResultDefault (wxDC &dc);
    void setFontResultResults (wxDC &dc);
    void setFontResultPhases (wxDC &dc);

    /**************************************************************************/

private:
    configClass *m_config;
    cycleDataClass *m_cycleData;
    utilClass m_util;


    // true - we draw on printer (or print preview window)
    // false - we draw on the main frame
    bool m_printing;

    // width of the data specific for card printed in the lesft window
    int m_cardDataWidth;

    // window top height
    int m_windowTopHeight;
    // X values how to locate entries in top window
    int m_windowTopEntriesStartX[4];

    // calculated height of cell
    int m_cellHeight;
    // calculated width of cells for each day
    int m_cellsWidth[MAXDAYSONCARD];

};

#endif
