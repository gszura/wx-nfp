/*******************************************************************************
//
// Name:        customWindowNotes.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "customWindowNotes.h"


BEGIN_EVENT_TABLE(customWindowNotes, wxScrolledWindow)
     EVT_PAINT  (customWindowNotes::OnPaint)
END_EVENT_TABLE()

/******************************************************************************/

/**
 *
 */
customWindowNotes::customWindowNotes(wxWindow *parent,
                                     configClass *config,
                                     wxWindowID winid,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name)
     : wxScrolledWindow(parent, winid, pos, size, style, name)
{
     m_parent = parent;
     m_config = config;
     SetBackgroundColour(m_config->colourBackground);

     //wxClientDC dc(this);
     //PrepareDC(dc);
     //parent->PrepareDC(dc);
}

/******************************************************************************/

/**
 * Method runs on OnPaint event.
 */
void customWindowNotes::OnPaint(wxPaintEvent &WXUNUSED(event))
{
     if ( ! m_config->visibleNote.IsEmpty() ) {
          wxPaintDC dc(this);
          PrepareDC(dc);
          m_parent->PrepareDC(dc);

          SetBackgroundColour(m_config->colourBackground);

          dc.Clear();

          wxRect rect = GetRect();
          int x1 = dc.DeviceToLogicalX(0);
          dc.SetFont( m_config->fontResultDefault );
          dc.SetTextForeground( m_config->fontResultDefaultColour );
          int w, h;
          dc.GetTextExtent( m_config->visibleNote, &w, &h );
          if (w > rect.width-6)
               SetSize(w+6, -1);

          dc.DrawRectangle( x1, 0, x1+rect.width, rect.height );

          dc.DrawText( m_config->visibleNote, x1+1, 1 );

          dc.SetPen( wxPen( m_config->colourBorders ) );
          dc.DrawLine( x1, 0, x1+rect.width-1, 0 );
          dc.DrawLine( x1, 0, x1, rect.height-1 );
          dc.DrawLine( x1, rect.height-1, x1+rect.width-1, rect.height-1 );
          dc.DrawLine( x1+rect.width-1, 0, x1+rect.width-1, rect.height-1 );

     }
}

/******************************************************************************/
