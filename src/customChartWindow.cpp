/*******************************************************************************
//
// Name:        customChartWindow.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "customChartWindow.h"

BEGIN_EVENT_TABLE( customChartWindow, wxScrolledWindow )
    EVT_PAINT( customChartWindow::OnPaint )
    EVT_LEFT_DOWN( customChartWindow::OnMouseClick )
    EVT_RIGHT_DOWN( customChartWindow::OnMouseClick )
    EVT_LEFT_DCLICK( customChartWindow::OnMouseDClick )
    EVT_MOTION( customChartWindow::OnMouseMotion )
END_EVENT_TABLE()

/******************************************************************************/

/**
 * Contructor
 */
customChartWindow::customChartWindow( wxWindow *parent, configClass *config, cycleDataClass *cycleData, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
    : wxScrolledWindow( parent, winid, pos, size, style, name )
{
    m_parent = parent;
    m_config = config;
    m_cycleData = cycleData;
    a = 0;

    /*
    m_pixelsPerUnitX = 40;
    m_noUnitsX = 350;
    int xPos = 0;
    SetScrollbars( m_pixelsPerUnitX, 0, m_noUnitsX, 0, xPos, 0 );
    */

    SetBackgroundColour( config->colourBackground );

    /*
    m_notesWindow = new customWindowNotes( this, config, ID_NOTESWINDOW, wxPoint( 0, 0 ), wxSize( 1000, 20 ), wxNO_BORDER | wxNO_FULL_REPAINT_ON_RESIZE );
    m_notesWindow->SetFont( wxFont( 7, wxSWISS, wxNORMAL, wxNORMAL, FALSE, wxT( "Small Fonts" ) ) );
    m_notesWindow->Hide();
    */
}


customChartWindow::~customChartWindow()
{
}

void customChartWindow::setChart(chart *visibleChart, bool refreshData)
{
    m_chart = visibleChart;

    if (refreshData)
        m_chart->updateChartData();
}

/**
 * Method runs on OnPaint event.
 */
void customChartWindow::OnPaint( wxPaintEvent &WXUNUSED( event ) )
{
    int width, heigh;
    this->GetSize( &width, &heigh );

    SetBackgroundColour( m_config->colourBackground );

    wxPaintDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    dc.Clear();

    m_chart->printChart(width, heigh, dc);
    m_chart->drawTitle(dc);


    /*

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
    */
}

/******************************************************************************/

/**
 * OnMouseClick
 */
void customChartWindow::OnMouseClick( wxMouseEvent &event )
{
    /*
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
    */
}

/******************************************************************************/

/**
 *
 */
void customChartWindow::OnMouseDClick( wxMouseEvent &event )
{
    /*
    m_dayFrm->update();
    m_dayFrm->Show();
    */
}

/******************************************************************************/

/**
 *
 */
void customChartWindow::OnMouseMotion( wxMouseEvent &event )
{
    /*
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
    */
}

/******************************************************************************/
