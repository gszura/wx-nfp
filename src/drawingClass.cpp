/*******************************************************************************
//
// Name:        drawingClass.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "drawingClass.h"

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Constructor
 */
drawingClass::drawingClass( configClass *config, cycleDataClass *cycleData, bool printing )
{
    m_config = config;
    m_cycleData = cycleData;
    m_printing = printing;

    m_windowTopHeight = 40; // off-line
    m_windowTopEntriesStartX[0] = 150;
    m_windowTopEntriesStartX[1] = 280;
    m_windowTopEntriesStartX[2] = 450;
    m_windowTopEntriesStartX[3] = 650;

    m_cellHeight = 15;
    m_cellsWidth[0] = m_config->widowLeftWidth;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Draw data in the top header (info window)
 */
void drawingClass::drawInfoHead( wxDC &dc, int cardNo, int pageNo )
{
    wxCoord w, h;
    int x;
    int y = m_windowTopHeight / 2 + 1;
    wxString str;

    wxString cardNoStr = _T( "?/?" );
    wxString date = _T( "?" );
    wxString name = _T( "?" );
    wxString age = _T( "?" );
    wxString tempCorrectionMouth = _T( "?" );
    wxString tempCorrectionRectum = _T( "?" );
    wxString tempCorrectionVagina = _T( "?" );
    bool cardLocked = false;
    wxString cardNote = wxEmptyString;

    // set data in variables
    if ( m_cycleData->getCardsCount() > 0 && cardNo > 0 ) {
        cardEntry *card = m_cycleData->getCard( cardNo );
        wxDateTime firstDayOfCycle = card->getFirstDayOfCycle();

        //cardNoStr = m_util.intToStr( cardNo ) + _T( " / " ) + m_util.intToStr( m_cycleData->getCardsCount() );
        cardNoStr = wxString::Format( _T( "%i / %i" ), cardNo, m_cycleData->getCardsCount() );
        if ( m_printing && pageNo > 0 ) {
            //cardNoStr = m_util.intToStr( cardNo ) + _T( " (" ) + m_util.intToStr( pageNo ) + _( ") / " ) + m_util.intToStr( m_cycleData->getCardsCount() );
            cardNoStr = wxString::Format( _T( "%i (%i) / %i" ), cardNo, pageNo, m_cycleData->getCardsCount() );
        }

        date = firstDayOfCycle.Format( _T( "%B %Y" ) );
        name = m_cycleData->getName();
        age = m_util.intToStr( m_util.strToInt( firstDayOfCycle.Format( _T( "%Y" ) ) ) - m_util.strToInt( m_cycleData->getBirthdayDay().Format( _T( "%Y" ) ) ) );

        if ( card->getTemperatureUsualMeasurementPlace() == PLACE_MOUTH )
            tempCorrectionMouth = _T( "-" );
        else
            tempCorrectionMouth = m_util.temperatureToStr( card->getTemperatureCorrectionWhenMeasuredInMouth(), true, true );
        if ( tempCorrectionMouth.IsEmpty() )
            tempCorrectionMouth = _T( "?" );

        if ( card->getTemperatureUsualMeasurementPlace() == PLACE_RECTUM )
            tempCorrectionRectum = _T( "-" );
        else
            tempCorrectionRectum = m_util.temperatureToStr( card->getTemperatureCorrectionWhenMeasuredInRectum(), true, true );
        if ( tempCorrectionRectum.IsEmpty() )
            tempCorrectionRectum = _T( "?" );

        if ( card->getTemperatureUsualMeasurementPlace() == PLACE_VAGINA )
            tempCorrectionVagina = _T( "-" );
        else
            tempCorrectionVagina = m_util.temperatureToStr( card->getTemperatureCorrectionWhenMeasuredInVagina(), true, true );
        if ( tempCorrectionVagina.IsEmpty() )
            tempCorrectionVagina = _T( "?" );

        cardLocked = card->getCardLocked();
        cardNote = card->getNotes();
    }

    // PRINT DATA ON THE SCREEN / PRINTER

    // cycleObservationcard
    setFontHeadTopic( dc );
    str = _( "Cycle observation" );
    //dc.DrawLabel(_T(" ") + text + _T(" "), wxRect(x,y,w,h));
    dc.DrawText( str, 1, 1 );
    dc.GetTextExtent( str, &w, &h );
    str = _( "card" );
    dc.DrawText( str, 1, y );

    // name
    setFontHeadValue( dc );
    x = m_windowTopEntriesStartX[0];
    str = name;
    dc.DrawText( str, x, 1 );
    dc.GetTextExtent( str, &w, &h );
    x += w + 10;
    setFontHeadName( dc );
    str = _( "age: " );
    dc.DrawText( str, x, 1 );
    dc.GetTextExtent( str, &w, &h );
    setFontHeadValue( dc );
    str = age;
    dc.DrawText( str, x + w, 1 );

    // CardNo
    x = m_windowTopEntriesStartX[0];
    setFontHeadName( dc );
    str = _( "card number: " );
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    setFontHeadValue( dc );
    str = cardNoStr;
    dc.DrawText( str, x + w, y );

    // date
    x = m_windowTopEntriesStartX[1];
    setFontHeadName( dc );
    str = _( "date: " );
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    setFontHeadValue( dc );
    str = date;
    dc.DrawText( str, x + w, y );

    // tempCorrection header
    x = m_windowTopEntriesStartX[2];
    setFontHeadName( dc );
    str = _( "temp. correction when measured in:" );
    dc.DrawText( str, x, 1 );

    // tempCorrectionRectum
    setFontHeadName( dc );
    str = _("mouth: ");
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    x += w;
    setFontHeadValue( dc );
    str = tempCorrectionMouth;
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    x += w + 5;
    // tempCorrectionRectum
    setFontHeadName( dc );
    str = _("rectum: ");
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    x += w;
    setFontHeadValue( dc );
    str = tempCorrectionRectum;
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    x += w + 5;
    // tempCorrectionVagina
    setFontHeadName( dc );
    str = _("vagina: ");
    dc.DrawText( str, x, y );
    dc.GetTextExtent( str, &w, &h );
    x += w;
    setFontHeadValue( dc );
    str = tempCorrectionVagina;
    dc.DrawText( str, x, y );

    x = m_windowTopEntriesStartX[3];
    // card locked
    if ( cardLocked ) {
        setFontHeadValue( dc );
        dc.SetTextForeground( wxColour( 255, 0, 0 ) );
        str = _( "card locked" );
        dc.DrawText( str, x, 1 );
    }

    // card's notes
    if ( ! cardNote.IsEmpty() ) {
        setFontHeadValue( dc );
        dc.DrawText( cardNote, x, y );
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Draw data in the first column (header)
 */
void drawingClass::drawHeader( wxDC &dc, int cardNo )
{



    int row = 0;
    int x = 0;
    int y0 = m_config->verticalDisplacement;
    if ( m_printing )
        y0 = m_windowTopHeight;
    int y = y0;
    int w = m_cellsWidth[0];
    int h = m_cellHeight;

    wxString temperatureUsualMeasurementTime = wxEmptyString;
    wxString temperatureUsualMeasurementPlace = wxEmptyString;
    if ( m_cycleData->getCardsCount() > 0 && cardNo > 0 ) {
        cardEntry *card = m_cycleData->getCard( cardNo );
        temperatureUsualMeasurementTime = card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );
        int dataInt = card->getTemperatureUsualMeasurementPlace();
        switch ( dataInt ) {
        case PLACE_MOUTH: {
            temperatureUsualMeasurementPlace = string_placeMouth ;
            break;
        }
        case PLACE_RECTUM: {
            temperatureUsualMeasurementPlace = string_placeRectum;
            break;
        }
        case PLACE_VAGINA: {
            temperatureUsualMeasurementPlace = string_placeVagina;
            break;
        }
        default: {
            temperatureUsualMeasurementPlace = wxEmptyString;
            break;
        }
        }
    }

    setFontResultHeader( dc );

    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "menstruation" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "coitus record" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "day of week" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "day of month" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "other disturbances" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "temperature disturbances" ) );
    row++;
    y += h;

    for ( int i = 0; i < m_config->rowsCountTemp; i++ ) {
        int tt = m_config->temperatureRangeHigh - ( 5 * i );
        wxString temp = m_util.intToStr( tt / 100 ) + _T( "," );
        tt = tt % 100;
        if ( tt == 5 )
            temp += _T( "05" );
        else if ( tt % 10 == 0 )
            temp += m_util.intToStr( tt / 10 );
        else
            temp += m_util.intToStr( tt );

        drawText( dc, 0, row, x, y, w, h, wxALIGN_RIGHT, temp );
        row++;
        y += h;
    }

    wxCoord width, heigh;
    int row2 = m_config->rowsCountAboveTemp;
    dc.GetTextExtent( _( "chart" ), &width, &heigh );
    drawText( dc, 0, row2, x, y0 + ( row2*h ), width + 10, h, wxALIGN_LEFT, _( "chart" ) );
    row2 += 3;

    dc.GetTextExtent( _( "usual" ), &width, &heigh );
    int cw = width;
    dc.GetTextExtent( _( "time of" ), &width, &heigh );
    if ( width > cw )
        cw = width;
    dc.GetTextExtent( _( "measurement" ), &width, &heigh );
    if ( width > cw )
        cw = width;
    cw += 10;
    m_cardDataWidth = cw;

    drawText( dc, 0, row2,   x, y0 + ( row2*h ),   cw, h, wxALIGN_RIGHT, _( "usual" ) );
    drawText( dc, 0, row2 + 1, x, y0 + ( row2 + 1 ) *h, cw, h, wxALIGN_RIGHT, _( "time of" ) );
    drawText( dc, 0, row2 + 2, x, y0 + ( row2 + 2 ) *h, cw, h, wxALIGN_RIGHT, _( "measurement" ) );
    setFontResultDefault( dc );
    drawText( dc, 0, row2 + 3, x, y0 + ( row2 + 3 ) *h, cw, h, wxALIGN_RIGHT, temperatureUsualMeasurementTime );

    setFontResultHeader( dc );
    drawText( dc, 0, row2 + 4, x, y0 + ( row2 + 4 ) *h, cw, h, wxALIGN_RIGHT, _( "place of" ) );
    drawText( dc, 0, row2 + 5, x, y0 + ( row2 + 5 ) *h, cw, h, wxALIGN_RIGHT, _( "measurement" ) );
    setFontResultDefault( dc );
    drawText( dc, 0, row2 + 6, x, y0 + ( row2 + 6 ) *h, cw, h, wxALIGN_RIGHT, temperatureUsualMeasurementPlace );

    setFontResultHeader( dc );
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "measured temperature" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "measurement time" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "measurement place" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "additional temp. correction" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "mucus - feeling, experience" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "mucus - appearance" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "mucus - peak" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h*2, wxALIGN_LEFT, _( "cervix - position, dilation" ) );
    row++;
    y += h * 2;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "cervix - hardness" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "cervix - peak" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "ovulation pain" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "breasts tension" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "spotting" ) );
    row++;
    y += h;
    drawText( dc, 0, row, x, y, w, h, wxALIGN_LEFT, _( "additional notes" ) );

    // draw borders
    h = m_cellHeight;
    dc.SetPen( wxPen( m_config->colourBorders ) );

    y = y0 + h * 7;
    dc.DrawLine( 0, y, w, y );
    y = y0 + h * ( 7 + m_config->rowsCountTemp + 4 );
    dc.DrawLine( 0, y, w, y );
    y = y0 + h * ( 7 + m_config->rowsCountTemp + 7 );
    dc.DrawLine( 0, y, w, y );
    y = y0 + h * ( 7 + m_config->rowsCountTemp + 11 );
    dc.DrawLine( 0, y, w, y );
    y = y0 + h * ( m_config->rowsCount + 1 );
    dc.DrawLine( 0, y, w, y );

    // vertical lines
    dc.DrawLine( w - 1, y0, w - 1, y );
    dc.DrawLine( 0,   y0, 0,   y );
    dc.DrawLine( cw, y0 + h*( 7 + 3 ), cw, y0 + h*( 7 + 3 + 7 ) );

    // draw the first row
    y = 0;
    if ( m_printing )
        y = y0;

    // draw borders in the first row
    drawText( dc, 0, 0, x, y, w, h, wxALIGN_LEFT, _( "day of cycle" ) );
    dc.SetPen( wxPen( m_config->colourBorders ) );
    dc.DrawLine( 0, y, w, y );
    dc.DrawLine( 0, y + h, w, y + h );
    dc.DrawLine( w - 1, y, w - 1, y + h );
    dc.DrawLine( 0, y, 0, y + h );
}

/**
 * Update card related data in the first column (header)
 */
void drawingClass::drawCardDataInHeader( wxDC &dc, int cardNo )
{



    int x = 0;
    int y0 = m_config->verticalDisplacement;
    if ( m_printing )
        y0 = m_windowTopHeight;
    int h = m_cellHeight;
    int row2 = m_config->rowsCountAboveTemp + 3;
    int cw = m_cardDataWidth;

    wxString temperatureUsualMeasurementTime = wxEmptyString;
    wxString temperatureUsualMeasurementPlace = wxEmptyString;
    if ( m_cycleData->getCardsCount() > 0 && cardNo > 0 ) {
        cardEntry *card = m_cycleData->getCard( cardNo );
        temperatureUsualMeasurementTime = card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );
        int dataInt = card->getTemperatureUsualMeasurementPlace();
        switch ( dataInt ) {
        case PLACE_MOUTH: {
            temperatureUsualMeasurementPlace = string_placeMouth ;
            break;
        }
        case PLACE_RECTUM: {
            temperatureUsualMeasurementPlace = string_placeRectum;
            break;
        }
        case PLACE_VAGINA: {
            temperatureUsualMeasurementPlace = string_placeVagina;
            break;
        }
        default: {
            temperatureUsualMeasurementPlace = wxEmptyString;
            break;
        }
        }
    }

    setFontResultDefault( dc );
    drawText( dc, 0, row2 + 3, x, y0 + ( row2 + 3 ) *h, cw, h, wxALIGN_RIGHT, temperatureUsualMeasurementTime );
    drawText( dc, 0, row2 + 6, x, y0 + ( row2 + 6 ) *h, cw, h, wxALIGN_RIGHT, temperatureUsualMeasurementPlace );
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void drawingClass::drawCard( wxDC &dc, int cardNo, int firstDay, int lastDay )
{
    if ( m_cycleData->getCardsCount() > 0 && cardNo > 0 ) {
        cardEntry *card = m_cycleData->getCard( cardNo );
        wxDateTime date = card->getFirstDayOfCycle();
        date.Add( wxDateSpan::Days( firstDay - 1 ) );
        wxString usualMeasurementTime = card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );

        int x = 0;
        if ( !m_printing )
            for ( int i = 1; i < firstDay; i++ )
                x += m_cellsWidth[i];
        else
            x = m_cellsWidth[0];


        for ( int dayNo = firstDay; dayNo <= lastDay; dayNo++ ) {
            drawDay( dc, cardNo, dayNo, x, date, usualMeasurementTime );
            date.Add( wxDateSpan::Days( 1 ) );
            x += m_cellsWidth[dayNo];
        }

        // TEMPERATURE GRAPH
        drawTemperatureGraph( dc, cardNo, firstDay );
    } else {
        // TODO assert
    }
}

void drawingClass::markDay( wxDC &dc, int cardNo, int dayNo, bool doMark )
{
    if ( m_cycleData->getCardsCount() > 0 && cardNo > 0 ) {

        int x1 = 0;
        for ( int i = 1; i < dayNo; i++ )
            x1 += m_cellsWidth[i];
        int x2 = x1 + m_cellsWidth[dayNo];

        if (doMark) {
            dc.SetPen( wxPen( m_config->colourMarkedBorders ) );
        } else {
            dc.SetPen( wxPen( m_config->colourBorders ) );
        }
        //dc.DrawLine( x1, 0, x2, 0 );
        dc.DrawLine( x1, m_cellHeight, x2, m_cellHeight );
    } else {
        // TODO assert
    }
}

void drawingClass::markRow( wxDC &dc, int rowNo, bool doMark )
{
    int x = m_cellsWidth[0] - 1;
    int y1 = rowNo * m_cellHeight;
    int y2 = y1 + m_cellHeight;

    if (doMark) {
        dc.SetPen( wxPen( m_config->colourMarkedBorders ) );
    } else {
        dc.SetPen( wxPen( m_config->colourBorders ) );
    }
    dc.DrawLine( x, y1, x, y2 );
    //dc.DrawLine( 100, y1, 200, y2 );
}


/******************************************************************************/

/**
 * first day == 1 (0 == header).
 */
void drawingClass::drawDay( wxDC &dc, int cardNo, int dayNo, int x0, wxDateTime date, wxString usualMeasurementTime )
{
    int x = x0;
    int y = m_config->verticalDisplacement;
    if ( m_printing )
        y = m_windowTopHeight;
    int y0 = y;
    int w   = 0;
    int h   = 0;
    int row = 0;
    wxString dataString;
    int dataInt;

    w = m_cellsWidth[dayNo];
    h = m_cellHeight;

    cardEntry *card = m_cycleData->getCard( cardNo );
    dayEntry * day = m_cycleData->getDay( cardNo, dayNo );

    if ( day != NULL ) {
        /* draw content from the day */
        setFontResultDefault( dc );

        row++;
        y += h;

        /* Menstruation */
        drawCrossOrSlash( dc, dayNo, row, x, y, w, h, day->getMenstruation() );
        row++;
        y += h;
        /* CoitusRecord */
        setFontResultHeart( dc );
        drawHeart( dc, dayNo, row, x, y, w, h, day->getCoitusRecord() );
        setFontResultDefault( dc );
        row++;
        y += h;

        /* date - week day */
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, date.Format( _T( "%a" ) ) );
        row++;
        y += h;
        /* date - day.month */
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, date.Format( _T( "%d.%m" ) ) );
        row++;
        y += h;

        /* OtherDisturbances */
        if ( day->getOtherDisturbances() )
            drawVV( dc, dayNo, row, x, y, w, h, 1 );
        else
            drawVV( dc, dayNo, row, x, y, w, h, -1 );
        row++;
        y += h;
        /* TemperatureDisturbances */
        if ( day->getTemperatureDisturbances() )
            drawVV( dc, dayNo, row, x, y, w, h, 1 );
        else
            drawVV( dc, dayNo, row, x, y, w, h, -1 );
        row++;
        y += h;

        /* TEMPERATURE GRAPH BACKGROUND */
        for ( int i = 0; i < m_config->rowsCountTemp; i++ ) {
            drawCellBackground( dc, dayNo, row, x, y, w, h );
            row++;
            y += h;
        }

        /* TemperatureMeasuredValue */
        wxString measuredTemp = m_util.temperatureToStr( day->getTemperatureMeasuredValue(), false );
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, measuredTemp );
        row++;
        y += h;
        /* TemperatureMeasurementTime */
        dataString = day->getTemperatureMeasurementTime().Format( _T( "%H:%M" ) );
        if ( measuredTemp.IsEmpty() || dataString.IsSameAs( _T( "00:00" ) ) || dataString.IsSameAs( usualMeasurementTime ) ) {
            dataString = wxEmptyString;
        }
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        row++;
        y += h;
        /* TemperatureMeasurementPlace */
        dataInt = day->getTemperatureMeasurementPlace();
        if ( measuredTemp.IsEmpty() || dataInt == card->getTemperatureUsualMeasurementPlace() ) {
            dataString = wxEmptyString;
        } else {
            switch ( dataInt ) {
            case PLACE_MOUTH: {
                dataString = string_placeMouth ;
                break;
            }
            case PLACE_RECTUM: {
                dataString = string_placeRectum;
                break;
            }
            case PLACE_VAGINA: {
                dataString = string_placeVagina;
                break;
            }
            default: {
                dataString = wxEmptyString;
                break;
            }
            }
        }
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        row++;
        y += h;
        /* TemperatureAdditionalCorrection */
        if ( measuredTemp.IsEmpty() ) {
            drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, wxEmptyString );
        } else {
            drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, m_util.temperatureToStr( day->getTemperatureAdditionalCorrection(), true ) );
        }
        row++;
        y += h;

        /* mucus - feeling, experience */
        dataInt = day->getMucusFeelingExperience();
        switch ( dataInt ) {
        case MUCUS_DRY: {
            dataString = string_mucusDry;
            break;
        }
        case MUCUS_MOIST: {
            dataString = string_mucusMoist;
            break;
        }
        case MUCUS_WET: {
            dataString = string_mucusWet;
            break;
        }
        case MUCUS_SLIPPERY: {
            dataString = string_mucusSlippery;
            break;
        }
        default: {
            dataString = wxEmptyString;
            break;
        }
        }
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        row++;
        y += h;
        /* MucusAppearance */
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, day->convertMucusAppearance( day->getMucusAppearance() ) );
        row++;
        y += h;
        /* ResultMucusPeak */
        dataString = wxEmptyString;
        if ( card->isResultMucus1stDay(dayNo) )
            dataString = _T( "^" );
        else if ( card->isResultMucus1stMoreFertileDay(dayNo) )
            dataString = _T( "^^" );
        else if ( card->isResultMucusPeak(dayNo) )
            dataString = string_peakDay;
        else if ( card->isResultMucusPeak(dayNo-1) )
            dataString = _T( "1" );
        else if ( card->isResultMucusPeak(dayNo-2) )
            dataString = _T( "2" );
        else if ( card->isResultMucusPeak(dayNo-3) )
            dataString = _T( "3" );
        setFontResultResults( dc );
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        setFontResultDefault( dc );
        row++;
        y += h;

        /* CervixPosition */
        h = 2 * m_cellHeight;
        drawCervixOval( dc, dayNo, row, x, y, w, h, day->getCervixPosition(), day->getCervixDilation() );
        row++;
        y += h;
        h = m_cellHeight;
        /* CervixHardness */
        dataInt = day->getCervixHardness();
        switch ( dataInt ) {
        case CERVIX_SOFT: {
            dataString = string_cervixSoft;
            break;
        }
        case CERVIX_RATHER_FIRM: {
            dataString = string_cervixRatherFirm;
            break;
        }
        case CERVIX_FIRM: {
            dataString = string_cervixFirm;
            break;
        }
        default: {
            dataString = wxEmptyString;
            break;
        }
        }
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        row++;
        y += h;
        /* ResultCervixPeak */
        dataString = wxEmptyString;
        if ( card->isResultCervix1stDay(dayNo) )
            dataString = _T( "^" );
        else if ( card->isResultCervixPeak(dayNo) )
            dataString = string_peakDay;
        else if ( card->isResultCervixPeak(dayNo-1) )
            dataString = _T( "1" );
        else if ( card->isResultCervixPeak(dayNo-2) )
            dataString = _T( "2" );
        else if ( card->isResultCervixPeak(dayNo-3) )
            dataString = _T( "3" );
        setFontResultResults( dc );
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );
        setFontResultDefault( dc );
        row++;
        y += h;

        /* OvulationPain */
        drawVV( dc, dayNo, row, x, y, w, h, day->getOvulationPain() );
        row++;
        y += h;
        /* BreastsTension */
        drawVV( dc, dayNo, row, x, y, w, h, day->getBreastsTension() );
        row++;
        y += h;
        /* Spotting */
        drawVV( dc, dayNo, row, x, y, w, h, day->getSpotting() );
        row++;
        y += h;
        /* AdditionalNotes */
        dataString = day->getAdditionalNotes();
        if ( ! dataString.IsEmpty() )
            dataString = dataString.Mid( 0, 5 ) + _T( ".." );
        drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, dataString );


        /* draw phase line between phases */
        if ( card->isResultFertilePhaseStart(dayNo) || card->isResultInfertilePhaseStart(dayNo) ) {
            dc.SetPen( wxPen( m_config->colourPhaseLine ) );
            dc.DrawLine( x, y0, x, y0 + h*( m_config->rowsCount + 1 ) );
        }

        int y1 = 0;
        if ( m_printing )
            y1 = y0;

        /* draw first row ("day number") */
        drawText( dc, dayNo, 0, x, y1, w, h, wxALIGN_CENTER, m_util.intToStr( dayNo ) );

        /* draw borders */
        dc.SetPen( wxPen( m_config->colourBorders ) );
        y = y0 + h * 7;
        dc.DrawLine( x, y, x + w, y );
        y = y0 + h * ( 7 + m_config->rowsCountTemp + 4 );
        dc.DrawLine( x, y, x + w, y );
        y = y0 + h * ( 7 + m_config->rowsCountTemp + 7 );
        dc.DrawLine( x, y, x + w, y );
        y = y0 + h * ( 7 + m_config->rowsCountTemp + 11 );
        dc.DrawLine( x, y, x + w, y );
        y = y0 + h * ( m_config->rowsCount + 1 );
        dc.DrawLine( x, y, x + w, y );

        /* draw borders of the first row ("day number") */
        y = y1;
        dc.DrawLine( x, y, x + w, y );
        y += h;
        dc.DrawLine( x, y, x + w, y );
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void drawingClass::drawTemperatureGraph( wxDC &dc, int cardNo, int firstDay )
{
    // horizontal displacement (przesuniecie w poziomie) - needed for printing
    int x0 = 0;
    // vertical displacement (przesuniecie w pionie) - needed for printing
    int y0 = 0;

    if ( m_printing ) {
        x0 = m_cellsWidth[0];
        for ( int i = 1; i < firstDay; i++ )
            x0 -= m_cellsWidth[i];
        y0 = m_windowTopHeight;
    }

    /* height of the cell */
    int h = m_cellHeight;
    /* previous point */
    int lastDayNo = -1;
    /* coordinates of the previous point */
    int x1 = -1;
    int y1 = -1;
    /* coordinates of the current point */
    int x2 = -1;
    int y2 = -1;
    /* coordinates of the low and high levels (to draw the levels lines) */
    int xLowLevelStart = -1, xLowLevelEnd = -1, xHighLevelEnd = -1;
    /* Y-coordinate of the lowest possible temperature on the graph */
    int yMin = m_config->verticalDisplacement + ( m_config->rowsCountAboveTemp + m_config->rowsCountTemp ) * h - h / 2;

    cardEntry *card = m_cycleData->getCard( cardNo );

    /* creating temperatures table */
    wxString usualMeasurementTime = card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );
    int lowLevelStart = card->getResultTemperatureLowLevelStart();
    int yLowLevel = card->getResultTemperatureLowLevelValue();
    int highLevelStart = card->getResultTemperatureHighLevelStart();
    int highLevelEnd = card->getResultTemperatureHighLevelEnd();

    int *tempTab = new int[card->getDaysCount() + 1];

    for ( int dayNo = 1; dayNo <= card->getDaysCount(); dayNo++ ) {
        dayEntry *day = card->getDay( dayNo );
        tempTab[dayNo] = day->getTemperatureMeasuredValue();
        /* set x2 coordinate */
        if ( dayNo == 1 ) {
            x2 = 0;
        } else {
            x2 = x2 + m_cellsWidth[dayNo-1];
        }
        if ( tempTab[dayNo] > 0 ) {
            tempTab[dayNo] = day->getTemperatureValueAfterCorrections();

            if ( dayNo == lowLevelStart ) {
                xLowLevelStart = x2;
            } else if ( dayNo == highLevelStart ) {
                xLowLevelEnd = x2;
            } else if ( dayNo == highLevelEnd ) {
                xHighLevelEnd = x2 + m_cellsWidth[dayNo];
            }
        }
    }

    /* drawing phases names */
    // period of relative infertility
    if ( card->isResultFertilePhaseStart() || card->isResultInfertilePhaseStart() ) {
        setFontResultPhases( dc );
        wxString str = string_infertile_phase;
        wxCoord pW, pH;
        dc.GetTextExtent( str, &pW, &pH );
        int pY = m_cellHeight * ( m_config->rowsCountAboveTemp ) + 3;

        if ( card->isResultFertilePhaseStart() ) {
            // if the fertile phase start is defined then draw 'infertile phase' string at the begining of the card
            if ( card->getResultFertilePhaseStart()[0] > 3 ) {
                str = string_infertile_phase;
            } else {
                str = _T( " I" );
            }
            dc.DrawLabel( str, wxRect( x0 + 3, y0 + pY, pW, pH ), wxALIGN_LEFT | wxALIGN_TOP );
        }

        int pX = 0;
        bool drawPhaseString = false;
        for (int i=1; i<card->getDaysCount(); i++) {
            if ( card->isResultFertilePhaseStart(i) ) {
                // draw 'fertile phase' string for the day 'i'
                str = string_fertile_phase;
                drawPhaseString = true;
            } else if ( card->isResultInfertilePhaseStart(i) ) {
                // draw 'infertile phase' string for the day 'i'
                str = string_infertile_phase;
                drawPhaseString = true;
            }

            if (drawPhaseString) {
                dc.DrawLabel( str, wxRect( x0 + pX + 3, y0 + pY, pW, pH ), wxALIGN_LEFT | wxALIGN_TOP );
                drawPhaseString = false;
            }

            pX += m_cellsWidth[i];
        }
    }


/* drawing low and high levels lines */
if ( xLowLevelStart > 0 )
{
    if ( xLowLevelEnd < 0 )
        xLowLevelEnd = x2 + m_cellsWidth[card->getDaysCount()];
    else if ( xHighLevelEnd < 0 )
        xHighLevelEnd = x2 + m_cellsWidth[card->getDaysCount()];

    int y = yMin - ((( yLowLevel - m_config->temperatureRangeLow ) / 5 ) * h );
    dc.SetPen( wxPen( m_config->colourTemperatureLevelLine, 3 ) );
    dc.DrawLine( x0 + xLowLevelStart + 3, y0 + y, x0 + xLowLevelEnd - 3, y0 + y );
    if ( xHighLevelEnd > 0 ) {
        y = y - 4 * h;
        dc.DrawLine( x0 + xLowLevelEnd + 3, y0 + y, x0 + xHighLevelEnd - 3, y0 + y );
    }
}


/*drawing temperature graph */
for ( int dayNo = 1; dayNo <= card->getDaysCount(); dayNo++ )
{
    /* set x2 coordinate */
    if ( dayNo == 1 ) {
        x2 = m_cellsWidth[1] / 2;
    } else {
        x2 = x2 + m_cellsWidth[dayNo-1] / 2 + m_cellsWidth[dayNo] / 2;
    }

    dayEntry *day = card->getDay( dayNo );

    if ( tempTab[dayNo] > 0 ) {
        /* set y2 coordinate */
        y2 = yMin - ((( tempTab[dayNo] - m_config->temperatureRangeLow ) / 5 ) * h );

        if ( day->getTemperatureDisturbances() ) {
            dc.SetPen( wxPen( m_config->colourPointNormal ) );
            dc.DrawLine( x0 + x2 - 3, y0 + y2 - 3, x0 + x2 + 4, y0 + y2 + 4 );
            dc.DrawLine( x0 + x2 - 3, y0 + y2 + 3, x0 + x2 + 4, y0 + y2 - 4 );
        } else {
            /* set x1 && y1 coordinates (previous point) */
            if ( lastDayNo > 0 ) {
                /* drawing line between previous point and current point */
                dc.SetPen( wxPen( m_config->colourTemperatureLine ) );
                dc.DrawLine( x0 + x1, y0 + y1, x0 + x2, y0 + y2 );
            }
            lastDayNo = dayNo;
            x1 = x2;
            y1 = y2;

            /* drawing current point */
            if ( dayNo >= lowLevelStart && dayNo < highLevelStart ) {
                dc.SetPen( wxPen( m_config->colourPointBefore ) );
                dc.SetBrush( wxBrush( m_config->colourPointBefore ) );
            } else if ( dayNo >= highLevelStart && dayNo <= highLevelEnd ) {
                dc.SetPen( wxPen( m_config->colourPointAfter ) );
                dc.SetBrush( wxBrush( m_config->colourPointAfter ) );
            } else {
                dc.SetPen( wxPen( m_config->colourPointNormal ) );
                dc.SetBrush( wxBrush( m_config->colourPointNormal ) );
            }
            dc.DrawCircle( x0 + x2, y0 + y2, 3 );
        }
    }
}
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void drawingClass::drawCellBackground( wxDC &dc, int dayNo, int row, int x, int y, int w, int h )
{
    setCellColour( dc, dayNo, row );
    dc.DrawRectangle( x, y, w, h );
}

/**
 * align: 1 - left, 2 - center, 3 - right
 */
void drawingClass::drawText( wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int align, wxString text )
{
    drawCellBackground( dc, dayNo, row, x, y, w, h );
    if ( ! text.IsEmpty() ) {
        dc.DrawLabel( _T( " " ) + text + _T( " " ), wxRect( x, y, w, h ), align | wxALIGN_CENTER_VERTICAL );
    }
}

/**
 *
 */
void drawingClass::drawCrossOrSlash( wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int data )
{
    drawCellBackground( dc, dayNo, row, x, y, w, h );
    if ( data == 1 ) {
        int x1 = x + w / 2;
        int y1 = y + h / 2;
        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLine( x1 - 3, y1 + 3, x1 + 4, y1 - 4 );
    } else if ( data == 2 ) {
        int x1 = x + w / 2;
        int y1 = y + h / 2;
        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLine( x1 - 3, y1 - 3, x1 + 4, y1 + 4 );
        dc.DrawLine( x1 - 3, y1 + 3, x1 + 4, y1 - 4 );
    }
}

/**
 *
 */
void drawingClass::drawHeart( wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int data )
{
    wxString output = wxEmptyString;
    for ( int i = 0; i < data; i++ ) {
        output += m_config->coitusRecordCharacter;
    }
    drawText( dc, dayNo, row, x, y, w, h, wxALIGN_CENTER, output );
}

/**
 *
 */
void drawingClass::drawVV( wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int data )
{
    drawCellBackground( dc, dayNo, row, x, y, w, h );
    if ( data == 1 || data == 2 ) {
        int x1 = x + w / 2;
        int y1 = y + h / 2;
        if ( data == 2 )
            x1 = x1 - 3;

        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawLine( x1 - 2, y1 - 3, x1, y1 + 3 );
        dc.DrawLine( x1, y1 + 3, x1 + 3, y1 - 3 );

        if ( data == 2 ) {
            x1 += 6;
            dc.DrawLine( x1 - 2, y1 - 3, x1, y1 + 3 );
            dc.DrawLine( x1, y1 + 3, x1 + 3, y1 - 3 );
        }
    }
}

/**
 *
 */
void drawingClass::drawCervixOval( wxDC &dc, int dayNo, int row, int x, int y, int w, int h, int position, int dilation )
{
    drawCellBackground( dc, dayNo, row, x, y, w, h );
    if ( position > 0 && dilation > 0 ) {
        int x1 = x + w / 2;
        int y1 = y + h - position * h / 6;
        dc.SetPen( wxPen( m_config->fontResultDefaultColour ) );
        dc.DrawCircle( x1, y1, dilation );
    }
}


/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Calculate the optimal height of the top window.
 * Note that the parameter 'm_config->windowTopHeight' is off-line - the result of this calculation
 * is only stored in the configuration file and will be used after restarting the application.
 */
int drawingClass::setWindowTopHeight( wxDC &dc )
{
    wxString str = _( "Examplegjy" );
    wxCoord width, height;
    setFontHeadTopic( dc );
    dc.GetTextExtent( str, &width, &height );
    m_windowTopHeight = 2 * height + 3;
    return m_windowTopHeight;
}

/**
 *
 */
void drawingClass::setWindowTopEntriesStartX( wxDC &dc )
{
    wxCoord w1, w2, h;
    int x; //, y;
    wxString str;

    wxString cardNo = _T( "?/?" );
    wxString date = _T( "?" );
    wxString name = _T( "?" );
    wxString age = _T( "?" );
    wxString tempCorrectionMouth = _T( "?" );
    wxString tempCorrectionRectum = _T( "?" );
    wxString tempCorrectionVagina = _T( "?" );


    cardNo = _T( "888 / 999" );
    if ( m_printing )
        cardNo = _T( "888 (33) / 999" );
    date = _( "2004, Pazdziernik" );
    name = _( "Genowefa Brzeczykowska" );
    tempCorrectionRectum = tempCorrectionMouth;


    /* cycleObservationCard */
    setFontHeadTopic( dc );
    str = _( "Cycle observation" );
    dc.GetTextExtent( str, &w1, &h );
    str = _( "card" );
    dc.GetTextExtent( str, &w2, &h );
    if ( w1 > w2 )
        m_windowTopEntriesStartX[0] = w1 + 30;
    else
        m_windowTopEntriesStartX[0] = w2 + 30;

    /* name */
    setFontHeadValue( dc );
    str = _T( "Joanna Maria Brzeczyszczykiewicz-Kwoka" );
    dc.GetTextExtent( str, &w1, &h );
    x = w1 + 10;
    str = _T( "88" );
    dc.GetTextExtent( str, &w1, &h );
    x += w1;
    setFontHeadName( dc );
    str = _( "age" );
    dc.GetTextExtent( str, &w1, &h );
    m_windowTopEntriesStartX[2] = m_windowTopEntriesStartX[0] + x + w1 + 40;

    /* CardNo */
    setFontHeadName( dc );
    str = _( "card number" );
    dc.GetTextExtent( str, &w1, &h );
    setFontHeadValue( dc );
    str = _T( "999 / 999" );
    dc.GetTextExtent( str, &w2, &h );
    m_windowTopEntriesStartX[1] = m_windowTopEntriesStartX[0] + w1 + w2 + 20;

    /* date */
    setFontHeadName( dc );
    str = _( "date" );
    dc.GetTextExtent( str, &w1, &h );
    setFontHeadValue( dc );
    str = _T( "Pazdziernik" );
    dc.GetTextExtent( str, &w2, &h );
    x = m_windowTopEntriesStartX[1] + w1 + w2 + 40;
    if ( x > m_windowTopEntriesStartX[2] )
        m_windowTopEntriesStartX[2] = x;


    /* tempCorrectionRectum */
    setFontHeadName( dc );
    str = wxString::Format( _T( "%s: " ), string_placeMouth );
    dc.GetTextExtent( str, &w1, &h );
    x = w1;
    str = wxString::Format( _T( "%s: " ), string_placeRectum );
    dc.GetTextExtent( str, &w1, &h );
    x += w1;
    str = wxString::Format( _T( "%s: " ), string_placeVagina );
    dc.GetTextExtent( str, &w1, &h );
    x += w1;

    setFontHeadValue( dc );
    str = _T( "+0,2" );
    dc.GetTextExtent( str, &w1, &h );
    x += 3 * w1 + 30;

    m_windowTopEntriesStartX[3] = m_windowTopEntriesStartX[2] + x;
}

/**
 * Calculate the optimal width of the left window.
 * Note that the parameter 'm_config->widowLeftWidth' ('m_cellsWidth[0]' in this class) is off-line - the result of this calculation
 * is only stored in the configuration file and will be used after restarting the application.
 */
int drawingClass::setHeaderWidth( wxDC &dc )
{
    wxCoord width, height;
    int ret = 150;

    setFontResultHeader( dc );
    dc.GetTextExtent( _( "temperature disturbances" ), &width, &height );
    if ( width + 2 > ret )
        ret = width + 2;
    dc.GetTextExtent( _( "additional temp. correction" ), &width, &height );
    if ( width + 2 > ret )
        ret = width + 2;
    dc.GetTextExtent( _( "mucus - feeling, experience" ), &width, &height );
    if ( width + 2 > ret )
        ret = width + 2;
    dc.GetTextExtent( _( "cervix - position, dilation" ), &width, &height );
    if ( width + 2 > ret )
        ret = width + 2;



    m_cellsWidth[0] = ret;
    return ret;
}

/**
 *
 */
int drawingClass::setCellHeight( wxDC &dc )
{
    wxString str = _T( "Examplegjy" );
    wxCoord width, height;
    setFontResultHeader( dc );
    dc.GetTextExtent( str, &width, &height );
    m_cellHeight = height + 3;
    return m_cellHeight;
}

/**
 *
 */
void drawingClass::setCellsWidth( wxDC &dc, int cardNo )
{
    for ( int i = 1; i < MAXDAYSONCARD; i++ ) {
        m_cellsWidth[i] = MINCELLWIDTH;
    }

    if ( m_cycleData->getCardsCount() > 0 && m_cycleData->getCard( cardNo ) > 0 ) {
        for ( int dayNo = 1; dayNo <= m_cycleData->getDaysCount( cardNo ); dayNo++ ) {
            setCellWidth( dc, cardNo, dayNo );
        }
    }
}

/**
 *
 */
void drawingClass::setCellWidth( wxDC &dc, int cardNo, int dayNo )
{
    wxString str;
    wxCoord width, height;

    dayEntry * day = m_cycleData->getDay( cardNo, dayNo );
    setFontResultDefault( dc );

    /* "33333" */
    str = _T( "33333" );
    dc.GetTextExtent( str, &width, &height );
    m_cellsWidth[dayNo] = width + 5;

    /* dd.mm */
    str = day->getTemperatureMeasurementTime().Format( _T( "%H:%M" ) );
    dc.GetTextExtent( str, &width, &height );
    if ( m_cellsWidth[dayNo] < width + 5 )
        m_cellsWidth[dayNo] = width + 5;

    /* CoitusRecord */
    setFontResultHeart( dc );
    str = wxEmptyString;
    for ( int i = 0; i < day->getCoitusRecord(); i++ ) {
        str += m_config->coitusRecordCharacter;
    }
    dc.GetTextExtent( str, &width, &height );
    if ( m_cellsWidth[dayNo] < width + 5 )
        m_cellsWidth[dayNo] = width + 5;
    setFontResultDefault( dc );

    /* TemperatureMeasurementPlace, if ot will be displayed */
    if ( day->getTemperatureMeasurementPlace() != m_cycleData->getCard( cardNo )->getTemperatureUsualMeasurementPlace() ) {
        switch ( day->getTemperatureMeasurementPlace() ) {
        case PLACE_MOUTH: {
            str = string_placeMouth;
            break;
        }
        case PLACE_RECTUM: {
            str = string_placeRectum;
            break;
        }
        case PLACE_VAGINA: {
            str = string_placeVagina;
            break;
        }
        default: {
            str = wxEmptyString;
            break;
        }
        }
        dc.GetTextExtent( str, &width, &height );
        if ( m_cellsWidth[dayNo] < width + 5 )
            m_cellsWidth[dayNo] = width + 5;
    }

    /* MucusAppearance */
    str = day->convertMucusAppearance( day->getMucusAppearance() );
    dc.GetTextExtent( str, &width, &height );
    if ( m_cellsWidth[dayNo] < width + 5 )
        m_cellsWidth[dayNo] = width + 5;

    /* AdditionalNotes */
    if ( ! day->getAdditionalNotes().IsEmpty() ) {
        str = day->getAdditionalNotes().Mid( 0, 5 ) + _T( ".." );
        dc.GetTextExtent( str, &width, &height );
        if ( m_cellsWidth[dayNo] < width + 5 )
            m_cellsWidth[dayNo] = width + 5;
    }
    if ( m_cellsWidth[dayNo] % 2 == 1 ) {
        m_cellsWidth[dayNo]++;
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Return calculated width of cell
 */
int drawingClass::getCellWidth( int day )
{
    if ( day < 0 || day > MAXDAYSONCARD )
        return -1;

    return m_cellsWidth[day];
}

/**
 * Return calculated height of cell
 */
int drawingClass::getCellHeight()
{
    return m_cellHeight;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Set pen and brush colour of the selected cell.
 */
void drawingClass::setCellColour( wxDC &dc, int x, int y )
{
    if ( !m_printing && x == m_cycleData->getActiveDay() ) {
        if ( y % 2 == 0 ) {
            dc.SetPen( wxPen( m_config->colourMarkedCell1 ) );
            dc.SetBrush( wxBrush( m_config->colourMarkedCell1 ) );
        } else {
            dc.SetPen( wxPen( m_config->colourMarkedCell2 ) );
            dc.SetBrush( wxBrush( m_config->colourMarkedCell2 ) );
        }
    } else if ( x % 2 == 0 ) {
        if ( y % 2 == 0 ) {
            dc.SetPen( wxPen( m_config->colourCell11 ) );
            dc.SetBrush( wxBrush( m_config->colourCell11 ) );
        } else {
            dc.SetPen( wxPen( m_config->colourCell12 ) );
            dc.SetBrush( wxBrush( m_config->colourCell12 ) );
        }
    } else {
        if ( y % 2 == 0 ) {
            dc.SetPen( wxPen( m_config->colourCell21 ) );
            dc.SetBrush( wxBrush( m_config->colourCell21 ) );
        } else {
            dc.SetPen( wxPen( m_config->colourCell22 ) );
            dc.SetBrush( wxBrush( m_config->colourCell22 ) );
        }
    }
}

/**
 * Set the font of the HeadTopic.
 */
void drawingClass::setFontHeadTopic( wxDC &dc )
{
    dc.SetFont( m_config->fontHeadTopic );
    dc.SetTextForeground( m_config->fontHeadTopicColour );
    dc.SetBackground( m_config->colourBackground );
    dc.SetTextBackground( m_config->colourBackground );
}

/**
 * Set the font of the HeadName.
 */
void drawingClass::setFontHeadName( wxDC &dc )
{
    dc.SetFont( m_config->fontHeadName );
    dc.SetTextForeground( m_config->fontHeadNameColour );
}

/**
 * Set the font of the HeadValue.
 */
void drawingClass::setFontHeadValue( wxDC &dc )
{
    dc.SetFont( m_config->fontHeadValue );
    dc.SetTextForeground( m_config->fontHeadValueColour );
}

/**
 * Set the font of the header.
 */
void drawingClass::setFontResultHeader( wxDC &dc )
{
    dc.SetFont( m_config->fontResultHeader );
    dc.SetTextForeground( m_config->fontResultHeaderColour );
}

/**
 * Set the delault font of the card.
 */
void drawingClass::setFontResultDefault( wxDC &dc )
{
    dc.SetFont( m_config->fontResultDefault );
    dc.SetTextForeground( m_config->fontResultDefaultColour );
}

/**
 * Set the font for the heart (coitusRecord).
 */
void drawingClass::setFontResultHeart( wxDC &dc )
{
    dc.SetFont( m_config->fontResultHeart );
    dc.SetTextForeground( m_config->fontResultHeartColour );
}

/**
 * Set the font for the results (mucus and cervix peaks).
 */
void drawingClass::setFontResultResults( wxDC &dc )
{
    dc.SetFont( m_config->fontResultResults );
    dc.SetTextForeground( m_config->fontResultResultsColour );
}

/**
 * Set the font for the results (phases).
 */
void drawingClass::setFontResultPhases( wxDC &dc )
{
    dc.SetFont( m_config->fontResultPhases );
    dc.SetTextForeground( m_config->fontResultPhasesColour );
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
