/*******************************************************************************
//
// Name:        customWindowMain.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "customWindowMain.h"
#include "cardFrame.h"

BEGIN_EVENT_TABLE( customWindowMain, wxScrolledWindow )
    EVT_PAINT( customWindowMain::OnPaint )
    EVT_LEFT_DOWN( customWindowMain::OnMouseClick )
    EVT_RIGHT_DOWN( customWindowMain::OnMouseClick )
    EVT_LEFT_DCLICK( customWindowMain::OnMouseDClick )
    EVT_MOTION( customWindowMain::OnMouseMotion )
END_EVENT_TABLE()

/******************************************************************************/

/**
 * Contructor
 */
customWindowMain::customWindowMain( wxWindow *parent, customWindowLeft *windowLeft, dayFrame *dayFrm, configClass *config, cycleDataClass *cycleData, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
    : wxScrolledWindow( parent, winid, pos, size, style, name )
{
    m_parent = parent;
    m_windowLeft = windowLeft;
    m_dayFrm = dayFrm;
    m_config = config;
    m_cycleData = cycleData;
    m_drawing = new drawingClass( config, cycleData );

    m_pixelsPerUnitX = 40;
    m_noUnitsX = 350;
    int xPos = 0;
    SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
    SetBackgroundColour( config->colourBackground );

    m_lastOpenedCard = -1;
    m_prevCommantedDay = -1;
    m_prevMarkedDay = -1;

    m_notesWindow = new customWindowNotes( this, config, ID_NOTESWINDOW, wxPoint( 0, 0 ), wxSize( 1000, 20 ), wxNO_BORDER | wxNO_FULL_REPAINT_ON_RESIZE );
    m_notesWindow->SetFont( wxFont( 7, wxSWISS, wxNORMAL, wxNORMAL, FALSE, wxT( "Small Fonts" ) ) );
    m_notesWindow->Hide();
}

/******************************************************************************/

/**
 * Method runs on OnPaint event.
 */
void customWindowMain::OnPaint( wxPaintEvent &WXUNUSED( event ) )
{

    SetBackgroundColour( m_config->colourBackground );

    wxPaintDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );


    dc.Clear();

    if ( m_cycleData == NULL ) {

        return;
    }

    if ( m_lastOpenedCard != m_cycleData->getActiveCard() ) {
        m_drawing->setCellHeight( dc );
        m_drawing->setCellsWidth( dc, m_cycleData->getActiveCard() );
        m_lastOpenedCard = m_cycleData->getActiveCard();
    }

    if ( m_cycleData->getActiveDay() > 0 ) {
        m_drawing->setCellWidth( dc, m_cycleData->getActiveCard(), m_cycleData->getActiveDay() );
    }

    int xLeft, xRight, h;
    xLeft = dc.DeviceToLogicalX( 0 );
    this->GetSize( &xRight, &h );
    xRight += xLeft;

    int visibleDay = -1;

    if ( m_config->checkCurrentDayVisibility ) {
        m_config->checkCurrentDayVisibility = false;
        if ( m_cycleData->getActiveDay() > 0 ) {
            visibleDay = m_cycleData->getActiveDay();
        }
    } else if ( m_config->checkFirstDayVisibility ) {
        m_config->checkFirstDayVisibility = false;
        if ( m_cycleData->getDaysCount() > 0 ) {
            visibleDay = 1;
        }
    } else if ( m_config->checkLastDayVisibility ) {
        m_config->checkLastDayVisibility = false;
        if ( m_cycleData->getDaysCount() > 0 ) {
            visibleDay = m_cycleData->getDaysCount();
        }
    }

    if ( visibleDay > 0 ) {
        // checking if current day is visible on the screen
        int xLeftDay = 0;
        for ( int i = 1; i < visibleDay; i++ ) {
            xLeftDay += getCellWidth( i );
        }
        int xRightDay = xLeftDay + getCellWidth( visibleDay );

        if ( xLeftDay < xLeft ) {
            // current day is not visible on the screen - it's hidden on the left side
            int xPos = ( xLeftDay / m_pixelsPerUnitX ) - 3;
            if ( xPos < 0 )
                xPos = 0;
            this->SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
        } else if ( xRightDay > xRight ) {
            // current day is not visible on the screen - it's hidden on the right side
            int xPos = ( xRightDay - xRight + xLeft ) / m_pixelsPerUnitX + 4;
            this->SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
        }
    }

    xLeft = dc.DeviceToLogicalX( 0 );
    this->GetSize( &xRight, &h );
    xRight += xLeft;

    // checking which days are visible on the screen
    int firstDay = 0, lastDay = 0;
    int tmp = 0;

    for ( int i = 1; i <= m_cycleData->getDaysCount(); i++ ) {
        if ( firstDay == 0 ) {
            if ( tmp > xLeft ) {
                firstDay = i - 1;
            }
        }
        if ( tmp > xRight ) {
            lastDay = i;
            break;
        }
        tmp += getCellWidth( i );
    }
    if ( firstDay == 0 ) {
        firstDay = 1;
    }
    if ( lastDay == 0 ) {
        lastDay = m_cycleData->getDaysCount();
    }

    // draw card
    m_drawing->drawCard( dc, m_cycleData->getActiveCard(), firstDay, lastDay );
}

/******************************************************************************/

/**
 * OnMouseClick
 */
void customWindowMain::OnMouseClick( wxMouseEvent &event )
{
    if ( m_cycleData->getActiveCard() < 1)
        return;

    if ( m_dayFrm == NULL ) {
        // TODO assert
        return;
    } else if ( m_dayFrm->IsShown() && !m_dayFrm->checkIfDataHasBeenChanged( true ) ) {
        return;
    } else if ( m_cycleData == NULL ) {

        return;
    } else if ( m_cycleData->getActiveCard() < 0 ) {
        // TODO assert
        return;
    }

    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    wxPoint pos = event.GetPosition();
    long posX = dc.DeviceToLogicalX( pos.x );

    int oldCurrentDay = -1;
    if ( m_cycleData->getActiveDay() > -1 ) {
        oldCurrentDay = m_cycleData->getActiveDay();
    }

    int tmp = 0;
    int d = 1;
    while ( tmp < posX ) {
        if ( d > m_cycleData->getDaysCount() ) {
            d = -1;

            break;
        }
        tmp += getCellWidth( d++ );
    }

    if ( d == -1 ) {
        m_cycleData->setActiveDay( -1 );
    } else {
        m_cycleData->setActiveDay( d - 1 );
    }



    if ( oldCurrentDay != m_cycleData->getActiveDay() ) {
        wxString usualMeasurementTime = m_cycleData->getCard()->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );
        if ( oldCurrentDay > -1 ) {
            // unmark "oldCurrentDay"

            wxDateTime date = m_cycleData->getCard()->getFirstDayOfCycle();
            date.Add( wxDateSpan::Days( oldCurrentDay - 1 ) );
            int x = 0;
            for ( int i = 1; i < oldCurrentDay; i++ )
                x += m_drawing->getCellWidth( i );
            m_drawing->drawDay( dc, m_cycleData->getActiveCard(), oldCurrentDay, x, date, usualMeasurementTime );
        }
        if ( m_cycleData->getActiveDay() > -1 ) {
            // mark "activeDay"

            wxDateTime date = m_cycleData->getCard()->getFirstDayOfCycle();
            date.Add( wxDateSpan::Days( m_cycleData->getActiveDay() - 1 ) );
            int x = 0;
            for ( int i = 1; i < m_cycleData->getActiveDay(); i++ )
                x += m_drawing->getCellWidth( i );
            m_drawing->drawDay( dc, m_cycleData->getActiveCard(), m_cycleData->getActiveDay(), x, date, usualMeasurementTime );

            if ( m_dayFrm->IsShown() )
                m_dayFrm->update();
        } else {
            if ( m_dayFrm->IsShown() )
                m_dayFrm->Hide();
        }
        m_drawing->drawTemperatureGraph( dc, m_cycleData->getActiveCard() );
    }
    event.Skip();
}

/******************************************************************************/

/**
 *
 */
void customWindowMain::OnMouseDClick( wxMouseEvent &event )
{
    if ( m_cycleData->getActiveCard() < 1 || m_cycleData->getActiveDay() < 1)
        return;

    m_dayFrm->update();
    m_dayFrm->Show();

}

/******************************************************************************/

/**
 *
 */
void customWindowMain::OnMouseMotion( wxMouseEvent &event )
{
    try {
        if ( m_cycleData == NULL || m_cycleData->getActiveCard() < 1 || m_cycleData->getDaysCount() < 1 ) {
            // TODO assert
            return;
        }

        wxClientDC dc( this );
        PrepareDC( dc );
        m_parent->PrepareDC( dc );

        wxPoint pos = event.GetPosition();

        if ( pos.x < 3 || pos.y <= 0 ) {
            if ( m_notesWindow->IsShown() ) {
                m_notesWindow->Hide();
            }
            markDayAndRow(dc, -1, -1);
            return;
        }

        long posX = dc.DeviceToLogicalX( pos.x );
        long posY = dc.DeviceToLogicalY( pos.y );
        int drawHeight = m_config->rowsCount * getCellHeight();
        int tmpX = 0;
        int dayNo = 1;

        int rowNo = (int)(posY-1) / getCellHeight();
        if (posY < getCellHeight() || posY > m_config->verticalDisplacement + drawHeight + getCellHeight())
            rowNo = -1;

        while ( tmpX < posX ) {
            if ( dayNo > m_cycleData->getDaysCount() ) {
                dayNo = -1;
                break;
            }
            tmpX += getCellWidth( dayNo++ );
        }

        dayNo--;
        tmpX -= getCellWidth( dayNo );

        // show or hide notes if needed
        if ( posY < m_config->verticalDisplacement + drawHeight || posY > m_config->verticalDisplacement + drawHeight + getCellHeight() || dayNo == -1) {
            if ( m_notesWindow->IsShown() )
                m_notesWindow->Hide();
        } else if ( m_prevCommantedDay != dayNo || !m_notesWindow->IsShown() ) {
            m_prevCommantedDay = dayNo;
            dayEntry *d = m_cycleData->getDay( dayNo );
            if (d != NULL)
                m_config->visibleNote = d->getAdditionalNotes();
            else {
                m_config->visibleNote = wxEmptyString;
            }
            if ( ! m_config->visibleNote.IsEmpty() ) {
                wxRect rect = wxRect( 5, ( m_config->verticalDisplacement + drawHeight - 2 * getCellHeight() ), -1, getCellHeight() + 2 );
                m_notesWindow->SetSize( rect );
                if ( !m_notesWindow->IsShown() )
                    m_notesWindow->Show();
                m_notesWindow->Refresh();
            } else if ( m_notesWindow->IsShown() )
                m_notesWindow->Hide();
        }

        markDayAndRow(dc, dayNo, rowNo);
    } catch ( ... ) {
        // TODO assert
    }
}


void customWindowMain::markDayAndRow(wxDC &dc, int dayNo, int rowNo)
{
    try {
        if (m_prevMarkedDay > 0)
            m_drawing->markDay( dc, m_cycleData->getActiveCard(), m_prevMarkedDay, false );
        m_prevMarkedDay = dayNo;
        if (dayNo > 0)
            m_drawing->markDay( dc, m_cycleData->getActiveCard(), dayNo, true );

        m_windowLeft->markRow(rowNo);
    } catch ( ... ) {
        // TODO assert
    }
}


/**
 * Method called when:
 * - data in active day has been changed
 * - active day has been changed
 * -
 */
void customWindowMain::repaint( int id )
{
    if ( id == ACTIVE_DAY_UPDATE ) {
        repaint_activeDayUpdated( false );
    } else if ( id == ACTIVE_DAY_UPDATE_WITH_TEMP ) {
        repaint_activeDayUpdated( true );
    } else if ( id == ACTIVE_DAY_CHANGED ) {
        repaint_activeDayChanged();
    } else {

    }
}

/**
 * Refresh view because data in active day has been changed
 */
void customWindowMain::repaint_activeDayUpdated( bool tempChanged )
{
    if ( m_cycleData == NULL ) {
        // TODO assert?
    }

    if ( m_cycleData->getActiveDay() < 1 ) {
        // TODO assert?
        return;
    }

    SetBackgroundColour( m_config->colourBackground );

    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    int firstDay = m_cycleData->getActiveDay();
    int lastDay = 0;

    int xLeft, xRight, h;
    xLeft = dc.DeviceToLogicalX( 0 );
    this->GetSize( &xRight, &h );
    xRight += xLeft;

    int activeDayPreviousWidth = getCellWidth( firstDay );
    m_drawing->setCellWidth( dc, m_cycleData->getActiveCard(), firstDay );

    if ( activeDayPreviousWidth == getCellWidth( firstDay ) ) {
        lastDay = firstDay;
    } else {
        // checking the last day visible on the screen
        int tmp = 0;
        for ( int i = 1; i <= m_cycleData->getDaysCount(); i++ ) {
            if ( tmp > xRight ) {
                lastDay = i;
                break;
            }
            tmp += getCellWidth( i );
        }
        if ( lastDay == 0 ) {
            lastDay = m_cycleData->getDaysCount();
        }
    }

    if ( tempChanged ) {
        if ( firstDay > 1 ) {
            for ( int i = firstDay - 1; i > 0; i-- ) {
                if ( m_cycleData->getDay( i ) != NULL && !m_cycleData->getDay( i )->getTemperatureDisturbances() && m_cycleData->getDay( i )->getTemperatureMeasuredValue() != -1 ) {
                    firstDay = i;
                    break;
                }
            }
        }
        if ( lastDay < m_cycleData->getDaysCount() ) {
            for ( int i = lastDay + 1; i <= m_cycleData->getDaysCount(); i++ ) {
                if ( m_cycleData->getDay( i ) != NULL &&  !m_cycleData->getDay( i )->getTemperatureDisturbances() && m_cycleData->getDay( i )->getTemperatureMeasuredValue() != -1 ) {
                    if ( lastDay == m_cycleData->getActiveDay() ) {
                        lastDay = i;
                        if ( lastDay > firstDay + 50 ) {
                            lastDay = firstDay + 50;
                        }
                    }
                    break;
                }
            }
        }
    }

    // draw card
    m_drawing->drawCard( dc, m_cycleData->getActiveCard(), firstDay, lastDay );

}

/**
 * Refresh view because active day has been changed
 */
void customWindowMain::repaint_activeDayChanged()
{



    if ( m_cycleData == NULL ) {

        return;
    }

    if ( m_cycleData->getActiveDay() < 1 ) {

        return;
    }

    SetBackgroundColour( m_config->colourBackground );

    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    // checking if current day is visible on the screen
    int xLeft, xRight, h;
    xLeft = dc.DeviceToLogicalX( 0 );
    this->GetSize( &xRight, &h );
    xRight += xLeft;
    int xLeftDay = 0;
    for ( int i = 1; i < m_cycleData->getActiveDay(); i++ ) {
        xLeftDay += getCellWidth( i );
    }
    int xRightDay = xLeftDay + getCellWidth( m_cycleData->getActiveDay() );

    if ( xLeftDay < xLeft ) {
        // current day is not visible on the screen - it's hidden on the left side
        int xPos = ( xLeftDay / m_pixelsPerUnitX ) - 3;
        if ( xPos < 0 )
            xPos = 0;
        this->SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
    } else if ( xRightDay > xRight ) {
        // current day is not visible on the screen - it's hidden on the right side
        int xPos = ( xRightDay - xRight + xLeft ) / m_pixelsPerUnitX + 4;
        this->SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
    }

    // draw card

    if ( m_cycleData->getPrevActiveDay() < m_cycleData->getActiveDay() ) {
        m_drawing->drawCard( dc, m_cycleData->getActiveCard(), m_cycleData->getPrevActiveDay(), m_cycleData->getActiveDay() );
    } else {
        m_drawing->drawCard( dc, m_cycleData->getActiveCard(), m_cycleData->getActiveDay(), m_cycleData->getPrevActiveDay() );
    }
}

/**
 * Repaint days from choosen range.
 */
void customWindowMain::repaint_daysUpdated( int dayNoFrom, int dayNoTo )
{
    if ( m_cycleData == NULL ) {
        return;
    }

    if ( dayNoFrom < 1 ) {
        return;
    }
    if ( dayNoTo < 1 ) {
        return;
    }

    SetBackgroundColour( m_config->colourBackground );

    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );


    m_drawing->drawCard( dc, m_cycleData->getActiveCard(), dayNoFrom, dayNoTo );


}

/******************************************************************************/

/**
 * Return calculated width of cell
 */
int customWindowMain::getCellWidth( int day )
{
    return m_drawing->getCellWidth( day );
}

/**
 * Return calculated height of cell
 */
int customWindowMain::getCellHeight()
{
    return m_drawing->getCellHeight();
}

/******************************************************************************/


