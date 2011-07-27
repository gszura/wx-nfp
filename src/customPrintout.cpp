/*******************************************************************************
//
// Name:        customPrintout.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "customPrintout.h"


/******************************************************************************/
/**
 *
 */
customPrintout::customPrintout( configClass *config,
                                cycleDataClass *cycleData,
                                int firstCard, int lastCard, bool printLegend,
                                wxChar *title )
     : wxPrintout( title )
{
     m_config = config;
     m_cycleData = cycleData;
     m_drawing = new drawingClass( m_config, m_cycleData, true );

     m_firstCard = firstCard;
     m_lastCard = lastCard;
     m_printLegend = printLegend;

     m_legendPrinted = false;
     m_maxHeight = 0;
     m_maxWidth = 0;
     m_scale = 0;
     m_currentCard = 0;
     m_currentPage = 0;
     m_numberOfPages = 0;
     for ( int i = 0; i < 30; i++ )
          m_startDays[i] = 0;
     m_notesStartY = 0;
}

/**
 *
 */
customPrintout::~customPrintout() {}

/******************************************************************************/
/**
 *
 */
bool customPrintout::OnBeginDocument( int startPage, int endPage )
{



     if ( !wxPrintout::OnBeginDocument( startPage, endPage ) )
          return false;

     return true;
}

/******************************************************************************/
/**
 * Check if everything has been printed already.
 */
bool customPrintout::HasPage( int pageNum )
{

     wxString log = _T( "currentCard=" ) + m_util.intToStr( m_currentCard );
     log += _T( ", lastCard=" ) + m_util.intToStr( m_lastCard );
     log += _T( ", currentPage=" ) + m_util.intToStr( m_currentPage );
     log += _T( ", numberOfPages=" ) + m_util.intToStr( m_numberOfPages );


     if ( m_currentCard < m_lastCard ) {

          return true;
     } else if ( m_currentPage < m_numberOfPages ) {

          return true;
     } else if ( m_printLegend && !m_legendPrinted ) {

          return true;
     } else {

          return false;
     }
}

/******************************************************************************/
/**
 * Print one page.
 * For each card calculate on how many pages the card has to be printed.
 */
bool customPrintout::OnPrintPage( int page )
{

     //

     wxDC *dc = GetDC();
     if ( dc ) {
          if ( m_currentCard == 0 ) {
               // beggining of printing
               CalculateUserScale( dc );
          }

          if ( m_currentCard == m_lastCard && m_currentPage == m_numberOfPages ) {
               PrintLegend( dc );
          } else {
               if ( m_currentCard == 0 ) {
                    // first page of the first printed card
                    m_currentCard = m_firstCard - 1;
               }
               if ( m_currentPage == m_numberOfPages ) {
                    m_currentCard++;
                    CalculatePagesNumber( dc );
                    m_currentPage = 0;
               }

               m_currentPage++;
               PrintPage( dc );
               PrintAdditionalNotes( dc );
          }

          return true;
     } else {

          return false;
     }
}

/******************************************************************************/
/**
 * Calculate and set the user scale.
 * The height of the single cell must be (CELLHEIGHT/10) milimeters.
 * Ths function has to be called once at the beggining of printing.
 */
void customPrintout::CalculateUserScale( wxDC *dc )
{
     // Get the size of the page in pixels
     int pageWidthPx, pageHeightPx;
     int pageWidthMm, pageHeightMm;
     GetPageSizePixels( &pageWidthPx, &pageHeightPx );
     GetPageSizeMM( &pageWidthMm, &pageHeightMm );

     // calculate cycle's graph basic sizes
     int windowTopHeight = m_drawing->setWindowTopHeight( *dc );
     m_drawing->setHeaderWidth( *dc );
     int cellHeight = m_drawing->setCellHeight( *dc );

     // Calculate a suitable scaling factor
     float yP = ( float ) pageHeightPx * ( float ) CELLHEIGHT / ( float )( pageHeightMm * 10 );
     m_scale = yP / ( float ) cellHeight;

     wxString log1 = _T( "" );
     log1 << _T( ", pageHeightPx=" ) << pageHeightPx;
     log1 << _T( ", pageHeightMm=" ) << pageHeightMm;
     log1 << _T( ", CELLHEIGHT=" ) << CELLHEIGHT;
     log1 << _T( ", yP=" ) << yP;
     log1 << _T( ", cellHeight=" ) << cellHeight;
     log1 << _T( ", m_scale=" ) << m_scale;


     // m_maxHeight of the printed card (plus legend)
     m_maxHeight = ( int )( pageHeightPx / m_scale );

     // maxX of the card, if card width is > maxX than it has to printed on more than one page
     m_maxWidth = ( int )( pageWidthPx / m_scale );

     // Y-coordinate where legend starts
     m_notesStartY = windowTopHeight + cellHeight * ( m_config->rowsCount + 1 );


     wxString log = _T( "userScale=" );
     log << m_scale;
     log << _T( ", maxWidth=" ) << m_maxWidth;
     log << _T( ", maxHeight=" ) << m_maxHeight;
     log << _T( ", m_notesStartY=" ) << m_notesStartY;

}

/******************************************************************************/
/**
 * Calculate cells width and on how many pages the card has to be printed.
 * Ths function has to be called once for each card.
 */
void customPrintout::CalculatePagesNumber( wxDC *dc )
{


     // calculate location of data in the info row
     m_drawing->setWindowTopEntriesStartX( *dc );

     // calculate days widths on cycle's graph
     m_drawing->setCellsWidth( *dc, m_currentCard );

     // max width (minus header width)
     int maxX = m_maxWidth - m_drawing->getCellWidth( 0 );

     m_numberOfPages = 0;
     int x = 0;
     int p = 0;

     if ( m_cycleData->getDaysCount( m_currentCard ) > 0 ) {
          m_numberOfPages++;
          m_startDays[p] = 1;
          p++;

          for ( int i = 1; i < m_cycleData->getDaysCount( m_currentCard ); i++ ) {
               x += m_drawing->getCellWidth( i );


               if ( x > maxX ) {
                    m_numberOfPages++;
                    m_startDays[p] = i;
                    p++;
                    x = m_drawing->getCellWidth( i );
               }
          }
     }


}

/******************************************************************************/
/**
 * Print one page.
 */
void customPrintout::PrintPage( wxDC *dc )
{



     int firstDay = m_startDays[m_currentPage-1];
     int lastDay = m_cycleData->getDaysCount( m_currentCard );
     if ( m_currentPage < m_numberOfPages )
          lastDay = m_startDays[m_currentPage] - 1;
     // needed to print number of printed page of current card
     int page = m_currentPage;
     if ( m_numberOfPages < 2 )
          page = -1;

     dc->SetUserScale( m_scale, m_scale );
     dc->SetBackground( m_config->colourBackground );
     dc->SetTextBackground( m_config->colourBackground );

     m_drawing->drawInfoHead( *dc, m_currentCard, page );
     m_drawing->drawCard( *dc, m_currentCard, firstDay, lastDay );
     m_drawing->drawHeader( *dc, m_currentCard );
}

/**
 * Print additional notes on the page.
 */
void customPrintout::PrintAdditionalNotes( wxDC *dc )
{



     int y = m_notesStartY + 5;
     int y0 = y;
     int x = 0;
     int x2 = 0;
     wxCoord width, height;
     wxString str = _T( "" );

     int firstDay = m_startDays[m_currentPage-1];
     int lastDay = m_cycleData->getDaysCount( m_currentCard );
     if ( m_currentPage < m_numberOfPages )
          lastDay = m_startDays[m_currentPage] - 1;

     // print header
     str = _( "additional notes:" );
     m_drawing->setFontResultHeader( *dc );
     dc->DrawText( str, x, y );

     dc->GetTextExtent( str, &width, &height );
     y += height;
     y0 = y;

     // print notes
     m_drawing->setFontResultDefault( *dc );

     for ( int dayNo = firstDay; dayNo <= lastDay; dayNo++ ) {
          str = m_cycleData->getDay( m_currentCard, dayNo )->getAdditionalNotes();
          if ( ! str.IsEmpty() ) {
               str = wxString::Format( _( "Day %i: %s" ), dayNo, str.c_str() );
               dc->DrawText( str, x, y );

               dc->GetTextExtent( str, &width, &height );
               y += height;
               if ( x2 < width )
                    x2 = width;

               if ( y + height > m_maxHeight ) {
                    // we are at the end of the page - start new column
                    y = y0;
                    x = x2;
               }
          }
     }
}

/**
 * Print legend.
 */
void customPrintout::PrintLegend( wxDC *dc )
{
     int y  = 0;
     //int y0 = 0;
     int x0 = 0;
     int x1 = 0;
     int x2 = 0;
     int x3 = 0;
     int h  = 0;
     int h1 = 5;
     int h2 = 2;
     wxCoord width, height;
     wxString str = _T( "" );

     dc->SetUserScale( m_scale, m_scale );
     dc->SetBackground( m_config->colourBackground );
     dc->SetTextBackground( m_config->colourBackground );

     // print header
     str = _( "Description of abbreviations used on cycles' card:" );
     m_drawing->setFontHeadTopic( *dc );
     dc->DrawText( str, x0, y );

     dc->GetTextExtent( str, &width, &height );
     y += height + h1 + h1;
     //y0 = y;

     // print legend
     m_drawing->setFontResultHeader( *dc );
     str = _T( "+,++,+++" );
     dc->GetTextExtent( str, &width, &height );
     h = height + 1;
     x1 = width / 2;
     x2 = width * 2;
     x3 = width * 5 / 2;

     /** mucusFeeling */
     y += h1;
     PrintLegendHeader( dc, _( "mucus - feeling, experience" ), x0, y );
     y += h + h2;
     PrintLegendEntry( dc, string_mucusDry, string_mucusDry_long, x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusMoist, string_mucusMoist_long, x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusWet, string_mucusWet_long, x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusSlippery, string_mucusSlippery_long, x1, x2, x3, y );
     y += h;

     /** mucusAppearance */
     y += h1;
     PrintLegendHeader( dc, _( "mucus - appearance" ), x0, y );
     y += h + h2;
     PrintLegendEntry( dc, string_mucusAppearanceOpaque, _( "o - opaque (the opposite of clear)" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusAppearanceWhite, _( "w - white" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusAppearanceYellowish, _( "y - yellowish" ), x1, x2, x3, y );
     y += h;
     // TODO - fix it to be able to use other length unit
     PrintLegendEntry( dc, string_mucusAppearanceTacky, _( "t - tacky (stretches up to 1 cm)" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusAppearanceClear, _( "c - clear (a more-fertile mucus)" ), x1, x2, x3, y );
     y += h;
     // TODO - fix it to be able to use other length unit
     PrintLegendEntry( dc, string_mucusAppearanceStretchy, _( "s - stretchy (stretches more than 1 cm)" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_mucusAppearanceSeminalResidue, _( "SR - seminal residue from marital relations" ) , x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, _T( "+,++,+++" ), _( "amount of mucus" ), x1, x2, x3, y );
     y += h;
     // TODO - fix it to be able to use other length unit
     PrintLegendEntry( dc, _T( "1,2,3.." ), _( "length of stretch in cm" ), x1, x2, x3, y );
     y += h;

     /** mucusPeak */
     y += h1;
     PrintLegendHeader( dc, _( "mucus - peak" ), x0, y );
     y += h + h2;
     PrintLegendEntry( dc, _T( "^" ), _( "First day of mucus apperance" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, _T( "^^" ), _( "First day of more fertile mucus apperance" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_peakDay, _( "Mucus peak day" ), x1, x2, x3, y );
     y += h;

     /** cervixPositionDilation */
     y += h1;
     PrintLegendHeader( dc, _( "cervix - position, dilation" ), x0, y );
     y += h + h2;
     PrintLegendHeader( dc, _( "position" ), x1, y );
     y += h + h2;
     PrintLegendCervixEntry( dc, CERVIX_HIGH, CERVIX_HALF_OPEN, string_cervixHigh_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_ABOVE_MIDDLE, CERVIX_HALF_OPEN, string_cervixAboveMiddle_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_IN_MIDDLE, CERVIX_HALF_OPEN, string_cervixInMiddle_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_BELOW_MEDDLE, CERVIX_HALF_OPEN, string_cervixBelowMiddle_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_LOW, CERVIX_HALF_OPEN, string_cervixLow_long, x1, x2, x3, y, h*2, width );
     y += h + h + h2;
     PrintLegendHeader( dc, _( "dilation" ), x1, y );
     y += h + h2;
     PrintLegendCervixEntry( dc, CERVIX_IN_MIDDLE, CERVIX_OPEN, string_cervixOpen_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_IN_MIDDLE, CERVIX_HALF_OPEN, string_cervixHalfOpen_long, x1, x2, x3, y, h*2, width );
     y += h + h;
     PrintLegendCervixEntry( dc, CERVIX_IN_MIDDLE, CERVIX_CLOSED, string_cervixClosed_long, x1, x2, x3, y, h*2, width );
     y += h + h;

     /** cervixHardness */
     y += h1;
     PrintLegendHeader( dc, _( "hardness" ), x0, y );
     y += h + h2;
     PrintLegendEntry( dc, string_cervixSoft, string_cervixSoft_long, x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_cervixRatherFirm, string_cervixRatherFirm_long, x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_cervixFirm, string_cervixFirm_long, x1, x2, x3, y );
     y += h;

     /** cervixPeak */
     y += h1;
     PrintLegendHeader( dc, _( "cervix - peak" ), x0, y );
     y += h + h2;
     PrintLegendEntry( dc, _T( "^" ), _( "First day of cervix changes" ), x1, x2, x3, y );
     y += h;
     PrintLegendEntry( dc, string_peakDay, _( "Cervix peak day" ), x1, x2, x3, y );
     y += h;

     /*
     rowNames.ovulationPain;
     rowNames.breastsTension;
     rowNames.spotting;
     rowNames.additionalNotes;
     rowNames.phase;
     */


     m_legendPrinted = true;
}

/**
 * Print legend.
 */
void customPrintout::PrintLegendHeader( wxDC *dc, wxString header, int x, int y )
{


     m_drawing->setFontResultHeader( *dc );
     dc->DrawText( header + _T( ":" ), x, y );
}

/**
 * Print legend.
 */
void customPrintout::PrintLegendEntry( wxDC *dc, wxString str1, wxString str3, int x1, int x2, int x3, int y )
{


     m_drawing->setFontResultHeader( *dc );
     dc->DrawText( str1, x1, y );
     m_drawing->setFontResultDefault( *dc );
     dc->DrawText( _T( "-" ), x2, y );
     dc->DrawText( str3, x3, y );
}

/**
 * Print legend.
 */
void customPrintout::PrintLegendCervixEntry( wxDC *dc, int p, int d, wxString str3, int x1, int x2, int x3, int y, int h, int w )
{


     m_drawing->drawCervixOval( *dc, 0, p + d, x1, y, w, h, p, d );
     //dc->DrawCircle (x1 + h / 2, y + h - p * h / 6, d);
     m_drawing->setFontResultDefault( *dc );
     dc->DrawText( _T( "-" ), x2, y );
     dc->DrawText( str3, x3, y );
}

/******************************************************************************/
