/*******************************************************************************
//
// Name:        customWindowLeft.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "customWindowLeft.h"


BEGIN_EVENT_TABLE( customWindowLeft, wxScrolledWindow )
    EVT_PAINT( customWindowLeft::OnPaint )
    EVT_LEFT_DOWN( customWindowLeft::OnMouseClick )
END_EVENT_TABLE()

/******************************************************************************/

/**
 *
 */
customWindowLeft::customWindowLeft( wxWindow *parent,
                                    configClass *config,
                                    cycleDataClass *cycleData,
                                    wxWindowID winid,
                                    const wxPoint& pos,
                                    const wxSize& size,
                                    long style,
                                    const wxString& name )
    : wxScrolledWindow( parent, winid, pos, size, style, name ) {
    m_parent = parent;
    m_config = config;
    m_cycleData = cycleData;
    m_drawing = new drawingClass( m_config, m_cycleData );
    SetBackgroundColour( m_config->colourBackground );

    wxClientDC dc( this );
    PrepareDC( dc );
    parent->PrepareDC( dc );
    m_lastOpenedCard = -1;
    m_prevMarkedRow  = -1;

}

/******************************************************************************/

/**
 *
 */
void customWindowLeft::OnMouseClick( wxMouseEvent &event ) {
}

/******************************************************************************/

/**
 * Method runs on OnPaint event.
 */
void customWindowLeft::OnPaint( wxPaintEvent &WXUNUSED( event ) ) {
    SetBackgroundColour( m_config->colourBackground );

    wxPaintDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    dc.Clear();

    if ( m_lastOpenedCard != m_cycleData->getActiveCard() ) {
        m_drawing->setCellHeight( dc );
        m_lastOpenedCard = m_cycleData->getActiveCard();
    }

    m_drawing->drawHeader( dc, m_cycleData->getActiveCard() );

}

/******************************************************************************/

/**
 * Repaint card specific data (usual temperature measurement time and place)
 */
void customWindowLeft::repaint_activeCardUpdated() {
    if ( m_cycleData == NULL ) {

        return;
    }

    if ( m_cycleData->getActiveCard() < 1 ) {

        return;
    }

    SetBackgroundColour( m_config->colourBackground );

    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );

    m_drawing->drawCardDataInHeader( dc, m_cycleData->getActiveCard() );
}

/******************************************************************************/
void customWindowLeft::recalculateComponentsSizes() {
    wxClientDC dc( this );
    PrepareDC( dc );
    m_parent->PrepareDC( dc );
    m_config->widowLeftWidth = m_drawing->setHeaderWidth( dc );
    m_drawing->setCellHeight( dc );
}

/******************************************************************************/

void customWindowLeft::markRow(int rowNo) {
    try {
        wxClientDC dc( this );
        PrepareDC( dc );
        m_parent->PrepareDC( dc );

        if (m_prevMarkedRow != -1)
            m_drawing->markRow( dc, m_prevMarkedRow, false );
        m_prevMarkedRow = rowNo;
        if (rowNo != -1)
            m_drawing->markRow( dc, rowNo, true );
    } catch ( ... ) {
        // TODO assert
    }

}

/******************************************************************************/
