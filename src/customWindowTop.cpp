/*******************************************************************************
//
// Name:        customWindowTop.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "customWindowTop.h"


BEGIN_EVENT_TABLE(customWindowTop, wxScrolledWindow)
     EVT_PAINT       (customWindowTop::OnPaint)
     EVT_LEFT_DCLICK (customWindowTop::OnMouseDClick)
END_EVENT_TABLE()

/******************************************************************************/

/**
 *
 */
customWindowTop::customWindowTop(wxWindow *parent,
                                 cardFrame *cardFrm,
                                 configClass *config,
                                 cycleDataClass *cycleData,
                                 wxWindowID winid,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 long style,
                                 const wxString& name)
     : wxScrolledWindow(parent, winid, pos, size, style, name)
{
     m_parent = parent;
     m_cardFrm = cardFrm;
     m_config = config;
     m_cycleData = cycleData;
     m_drawing = new drawingClass(m_config, m_cycleData);
     SetBackgroundColour(m_config->colourBackground);

     wxClientDC dc(this);
     PrepareDC(dc);
     m_parent->PrepareDC(dc);

     m_config->windowTopHeight = m_drawing->setWindowTopHeight(dc);
     m_drawing->setWindowTopEntriesStartX(dc);

}

/******************************************************************************/

/**
 * Mehtoh runs on double left click
 */
void customWindowTop::OnMouseDClick(wxMouseEvent &event)
{
    if ( m_cycleData->getActiveCard() < 1)
        return;

     m_cardFrm->update();
     m_cardFrm->Show();
}

/******************************************************************************/

/**
 * Method runs on OnPaint event.
 */
void customWindowTop::OnPaint(wxPaintEvent &WXUNUSED(event))
{
     SetBackgroundColour(m_config->colourBackground);

     wxPaintDC dc(this);
     PrepareDC(dc);
     m_parent->PrepareDC(dc);

     dc.Clear();

     dc.SetBackground( m_config->colourBackground );
     dc.SetTextBackground( m_config->colourBackground );
     m_drawing->drawInfoHead( dc, m_cycleData->getActiveCard() );

}

/******************************************************************************/
void customWindowTop::recalculateComponentsSizes()
{
     wxClientDC dc(this);
     PrepareDC(dc);
     m_parent->PrepareDC(dc);
     m_config->windowTopHeight = m_drawing->setWindowTopHeight(dc);
     m_drawing->setWindowTopEntriesStartX(dc);
}

/******************************************************************************/
